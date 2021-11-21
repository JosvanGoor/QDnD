#include "serverconnection.h"

////////////////////
//  Constructors  //
////////////////////

ServerConnection::ServerConnection(RuntimeModel *runtime_model, QObject *parent)
:   ConnectionBase(parent)
{
    d_server = new QTcpServer;
    d_runtime_model = runtime_model;

    QObject::connect(d_server, &QTcpServer::newConnection, this, &ServerConnection::on_new_connection);
    QObject::connect(&d_ping_timer, &QTimer::timeout, this, &ServerConnection::on_ping_timer);
    d_self.identifier = "Dungeon Master";
}


ServerConnection::~ServerConnection()
{
    delete d_server;
}


////////////////////
//     Public     //
////////////////////

void ServerConnection::start_listening(uint16_t port)
{
    if (!d_server->listen(QHostAddress::Any, port))
        emit connection_status_update("Failed to start listening to port " + QString::number(port));
    
    update_status();
    emit debug_message("Successfully started hosting");
    d_ping_timer.setInterval(45'000);
    d_ping_timer.start(45'000);
}


void ServerConnection::disconnect()
{
    for (auto it = d_connections.begin(); it != d_connections.end(); ++it)
    {
        it.value().socket->disconnect(this);
        it.value().socket->deleteLater();
    }

    d_server->close();
    d_connections.clear();
    d_ping_timer.stop();

    emit debug_message("Successfully stoped hosting");
    update_status();
}


bool ServerConnection::is_connected()
{
    return d_server->isListening();
}


bool ServerConnection::is_server()
{
    return true;
}


void ServerConnection::send(QJsonDocument const &doc, bool signal_self)
{
    QByteArray blob = doc.toJson();

    for (auto it = d_connections.begin(); it != d_connections.end(); ++it)
        send_blob(it.value().socket, blob);

    if (signal_self)
        signal_message(doc, d_self);
}


void ServerConnection::update_status()
{
    if (d_server->isListening())
        emit connection_status_update("Hosting @ " + QString::number(d_server->serverPort()) + " (" + QString::number(d_connections.size()) + " clients connected)");
    else
        emit connection_status_update("No Connection");
}


////////////////////
//    Incoming    //
////////////////////

void ServerConnection::host_special_message(QJsonDocument const &doc)
{
    handle_incoming_messages(doc, d_self);
}


void ServerConnection::handle_incoming_messages(QJsonDocument const &doc, SocketState &state)
{
    QJsonObject obj = doc.object();
    MessageType type = static_cast<MessageType>(obj["type"].toInt());
    debug_message("Handeling " + as_string(type));

    switch (type)
    {
        case MessageType::PONG: break; // we guchi
        
        case MessageType::PIXMAP_REQUEST:
        {
            bool start = state.file_queue.isEmpty();
            QJsonArray arr = obj["requests"].toArray();
            for (auto val : arr)
                state.file_queue.push_back(val.toString());

            if (start) // we are already uploading as is
                transfer_pixmap(state);
        }
        break;

        case MessageType::CHAT_MESSAGE:
            if (obj["message"].toString().startsWith("/roll", Qt::CaseInsensitive))
            {
                QString name = obj["name"].toString();
                QString expression = obj["message"].toString().mid(6);
                QString result = "";
                try
                {
                    DiceExpressionPtr expr = DiceParser::parse(expression);
                    DiceResult score = expr->evaluate();
                    result = score.text + " -> " + QString::number(score.result);
                }
                catch(std::runtime_error &err)
                {
                    result = err.what();
                }

                send(roll_message(name, expression, result), true);
                break;
            }
            
            signal_message(doc, state);
            send(doc); // dispatch to all clients.
        break;

        default:
            signal_message(doc, state);
            send(doc); // dispatch to all clients.
    }
}


void ServerConnection::transfer_pixmap(SocketState &state)
{
    debug_message("Transferring pixmap to " + state.identifier + ": " + state.file_queue.back());
    QString file = state.file_queue.back();
    state.file_queue.pop_back();

    TransferableImage img = d_runtime_model->pixmap_cache().prepare_for_transfer(file);
    if (img.name.isEmpty())
    {
        debug_message("Could not satisfy file request " + img.name);
        send_json_blob(state.socket, pixmap_not_found(file));
        return;
    }

    send_json_blob(state.socket, pixmap_transfer(img.name, img.b64_data));
}


////////////////////
//     Slots      //
////////////////////

void ServerConnection::on_ping_timer()
{
    emit debug_message("ping!");
    send(ping_message());
}


void ServerConnection::on_new_connection()
{
    QTcpSocket *socket;
    while ((socket = d_server->nextPendingConnection()) != nullptr)
    {
        emit debug_message("New Connection!");
        
        // TODO: request server state for new client
        d_connections[socket] = {socket, {}, 0, "", {}};
        QObject::connect(socket, &QTcpSocket::errorOccurred, this, &ServerConnection::on_socket_error);
        QObject::connect(socket, &QTcpSocket::readyRead, this, &ServerConnection::on_socket_readyread);
        QObject::connect(socket, &QTcpSocket::disconnected, this, &ServerConnection::on_socket_disconnected);
        update_status();
    }
}


void ServerConnection::on_socket_error(QAbstractSocket::SocketError error)
{
    QObject *id = QObject::sender();
    SocketState &state = d_connections.find(id).value();
    QString name = state.identifier.isEmpty() ? "[[Unknown]]" : state.identifier;
    
    QString errstr = QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error);
    emit debug_message(errstr + " from " + name);
}


void ServerConnection::on_socket_readyread()
{
    QObject *id = QObject::sender();
    SocketState &state = d_connections.find(id).value();
    QJsonDocument doc = read_connection(state);

    while (!doc.isEmpty())
    {
        handle_incoming_messages(doc, state);
        doc = read_connection(state);
    }
}


void ServerConnection::on_socket_readywrite([[maybe_unused]] uint64_t written)
{
    QObject *id = QObject::sender();
    SocketState &state = d_connections.find(id).value();
    
    // nothing to send, so we dont care
    if (state.file_queue.isEmpty())
        return;

    // socket is currently idle, so we can send a file
    if (state.socket->bytesToWrite() != 0)
        return;

    transfer_pixmap(state);
}


void ServerConnection::on_socket_disconnected()
{
    QObject *id = QObject::sender();
    SocketState &state = d_connections.find(id).value();

    if (!state.identifier.isEmpty())
    {
        send(disconnect_message(state.identifier), true);
    }

    state.socket->deleteLater();
    d_connections.remove(id);
    update_status();
}
