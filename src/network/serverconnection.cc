#include "serverconnection.h"

////////////////////
//  Constructor   //
////////////////////

ServerConnection::ServerConnection(QObject *parent)
:   ConnectionBase(parent)
{
    d_server = new QTcpServer;

    QObject::connect(d_server, &QTcpServer::newConnection, this, &ServerConnection::on_new_connection);
}


ServerConnection::~ServerConnection()
{
    d_server->deleteLater();
}


////////////////////
//       IO       //
////////////////////

void ServerConnection::dispatch(QByteArray const &data)
{
    for (auto &val : d_connections)
        write_blob(val.socket, data, true);
}


void ServerConnection::send(QByteArray const &data)
{
    dispatch(data);
}


void ServerConnection::send(QJsonDocument const &doc)
{
    dispatch(doc.toJson());
}


void ServerConnection::connect(QString const &host, uint16_t port)
{
    if (!host.isEmpty())
        emit debug_message("ServerConnection: received hostname for connect, this will be ignored.");

    bool success = d_server->listen(QHostAddress::Any, port);
    update_status();

    if (!success)
    {
        emit debug_message("Failed to start listening on port " + QString::number(port));
        return;
    }

    emit debug_message("Host successfully started listening");
    d_ping_timer.setInterval(45'000);
    d_ping_timer.start(45'000);
}


void ServerConnection::disconnect()
{
    for (auto &val : d_connections)
    {
        val.socket->disconnect(this);
        val.socket->deleteLater();
    }

    d_server->close();
    d_connections.clear();
    d_ping_timer.stop();

    emit debug_message("Stopped hosting.");
    update_status();
}


////////////////////
//    Messages    //
////////////////////

void ServerConnection::pre_handle_message(QJsonDocument const &doc)
{
    QJsonObject obj = doc.object();
    MessageType type = static_cast<MessageType>(obj["type"].toInt());
    debug_message("ServerConnection::handle_message [[" + as_string(type) + "]].");

    // handles only server specific messages, dispatches the rest.
    switch (type)
    {
        case MessageType::HANDSHAKE:
        {
            QString avatar_key = b64_pixmap_hash(obj["avatar"].toString().toLocal8Bit());
            QPixmap avatar_pixmap = pixmap_from_b64(obj["avatar"].toString().toLocal8Bit());
            emit pixmap_received(avatar_key, avatar_pixmap);
            obj["avatar"] = avatar_key;
            player_joins(obj);
        }
        return;

        case MessageType::PONG:
            // we actually dont do anything here
        return;

        default: break;
    }

    handle_message(doc);
    dispatch(doc.toJson());
}


void ServerConnection::message_to(QString const &identifier, QJsonDocument const &doc)
{
    SocketState *state = nullptr;
    for (auto &conn : d_connections)
    {
        if (conn.identifier == identifier)
        {
            state = &conn;
            break;
        }
    }

    if (state == nullptr)
    {
        debug_message("Failed to find connection for " + identifier + ", message not sent.");
        return;
    }

    write_json(state->socket, doc);
}


////////////////////
//    Utility     //
////////////////////

bool ServerConnection::is_server()
{
    return true;
}


void ServerConnection::update_status()
{
    if (d_server->isListening())
        emit connection_status("Hosting @ " + QString::number(d_server->serverPort()) + " (" + QString::number(d_connections.size()) + " connected).");
    else
        emit connection_status("No connection");
}


////////////////////
// Internal Slots //
////////////////////

void ServerConnection::on_ping_timer()
{
    // TODO: ping tracking
    send(ping_message());
}


void ServerConnection::on_new_connection()
{
    QTcpSocket *socket;
    while ((socket = d_server->nextPendingConnection()) != nullptr)
    {
        emit debug_message("New connection from " + socket->peerAddress().toString());

        // server->client state update will emitted from user manager after
        // the new client has sent handshake
        d_connections.insert(socket, {0, 0, socket, {}, ""});
        QObject::connect(socket, &QTcpSocket::errorOccurred, this, &ServerConnection::on_socket_error);
        QObject::connect(socket, &QTcpSocket::readyRead, this, &ServerConnection::on_socket_readyread);
        QObject::connect(socket, &QTcpSocket::disconnected, this, &ServerConnection::on_socket_disconnect);
        QObject::connect(socket, &QTcpSocket::bytesWritten, this, &ServerConnection::on_socket_readywrite);
        update_status();
    }
}


void ServerConnection::on_socket_error(QAbstractSocket::SocketError error)
{
    //TODO: signal user manager of disconnect
    QObject *id = QObject::sender();
    SocketState &state = d_connections.find(id).value();

    QString error_string = QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error);
    emit debug_message(error_string + " from " + state.socket->peerAddress().toString());
    //TODO: disconnect
}


void ServerConnection::on_socket_readyread()
{
    QObject *id = QObject::sender();
    SocketState &state = d_connections.find(id).value();
    QJsonDocument doc = read(state.socket, state.incoming, state.buffer);

    while (!doc.isEmpty())
    {
        pre_handle_message(doc);
        doc = read(state.socket, state.incoming, state.buffer);
    }
}


void ServerConnection::on_socket_readywrite([[maybe_unused]] uint64_t written)
{
    // TODO: queue pixmap request
}


void ServerConnection::on_socket_disconnect()
{
    QObject *id = QObject::sender();
    SocketState &state = d_connections.find(id).value();

    // TODO: notify user manager of disconnect

    state.socket->deleteLater();
    d_connections.remove(id);
    update_status();
}