#include "dataconnectionserver.h"

////////////////////
//  Constructor   //
////////////////////

DataConnectionServer::DataConnectionServer(uint16_t port, QObject *parent)
:   DataConnectionBase(parent)
{
    d_port = port;
    d_server = new QTcpServer;
}


DataConnectionServer::~DataConnectionServer()
{
    disconnect();
    emit connection_status("No connection");
}


////////////////////
//  Thread Main   //
////////////////////

void DataConnectionServer::run()
{
    QObject::connect(d_server, &QTcpServer::newConnection, this, &DataConnectionServer::on_new_connection);
    QObject::connect(&d_ping_timer, &QTimer::timeout, this, &DataConnectionServer::on_ping_timer);

    connect("", "", d_port);
    
    exec(); // run event loop
    
    for (auto &state : d_connections)
    {
        state.socket->disconnect(this);
        state.socket->deleteLater();
    }

    d_server->close();
    d_connections.clear();
    d_ping_timer.stop();
    // quit(); // stop event loop

    emit debug_message("Stopped data server.");
    update_status();
}


////////////////////
//    Virtuals    //
////////////////////

bool DataConnectionServer::is_server() const noexcept
{
    return true;
}


void DataConnectionServer::queue(QJsonDocument const &doc)
{
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    for (auto &state : d_connections)
    {
        state.queue.push_back(data);
        activate(state);
    }
}


void DataConnectionServer::connect(QString const &id, QString const &host, uint16_t port)
{
    if (!id.isEmpty())
        emit debug_message("DataConnectionServer: received id for connect, this will be ignored.");
    if (!host.isEmpty())
        emit debug_message("DataConnectionServer: received hostname for connect, this will be ignored.");

    bool success = d_server->listen(QHostAddress::Any, port);
    update_status();

    if (!success)
    {
        emit debug_message("DataServer failed to start listening on port " + QString::number(port));
        return;
    }

    emit debug_message("DataServer successfully started listening.");
    d_ping_timer.setInterval(45'000);
    d_ping_timer.start(45'000);
}


void DataConnectionServer::disconnect()
{
    quit();
}


////////////////////
//    Utility     //
////////////////////

void DataConnectionServer::update_status()
{
    if (d_server->isListening())
        emit connection_status("Hosting Data @ " + QString::number(d_server->serverPort()) + " (" + QString::number(d_connections.size()) + " connected).");
    else
        emit connection_status("No connection");
}


void DataConnectionServer::activate(DataSocketState &state)
{
    if (state.queue.isEmpty())
        return;
    
    if (state.socket->bytesToWrite() != 0)
        return;

    write_blob(state.socket, state.queue.back(), false);
    state.queue.pop_back();
}


DataSocketState *DataConnectionServer::state_by_identifier(QString const &id)
{
    for (auto &state : d_connections)
    {
        if (state.identifier == id)
            return &state;
    }
    return nullptr;
}


////////////////////
//     Slots      //
////////////////////

void DataConnectionServer::send_data_message(QString const &id, QJsonDocument const &doc)
{
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    DataSocketState *state = state_by_identifier(id);
    if (state == nullptr)
    {
        debug_message("Queuing message for " + id + " failed because the name was unknown.");
        return;
    }

    state->queue.push_back(data);
    activate(*state);
}


void DataConnectionServer::handle_message(QJsonDocument const &document, DataSocketState &state)
{
    MessageType type = static_cast<MessageType>(document["type"].toInt());
    debug_message("DataConnectionServer::handle_message [[" + as_string(type) + "]]");

    switch (type)
    {
        case MessageType::HANDSHAKE:
        {
            QString id = document["id"].toString();
            state.identifier = id;
        }
        return;

        case MessageType::PONG:
            // we ignore this message
        return;

        default: break;
    }

    emit message_received(document);
}


////////////////////
// Internal Slots //
////////////////////

void DataConnectionServer::on_ping_timer()
{
    QByteArray data = ping_message().toJson(QJsonDocument::Compact);
    
    // we insert it asap
    for (auto &state : d_connections)
        write_json(state.socket, ping_message());
}


void DataConnectionServer::on_new_connection()
{
    QTcpSocket *socket;
    while((socket = d_server->nextPendingConnection()) != nullptr)
    {
        emit debug_message("New data connection from " + socket->peerAddress().toString());

        d_connections.insert(socket, {0, 0, socket, {}, "", {}});
        QObject::connect(socket, &QTcpSocket::errorOccurred, this, &DataConnectionServer::on_socket_error);
        QObject::connect(socket, &QTcpSocket::readyRead, this, &DataConnectionServer::on_socket_readyread);
        QObject::connect(socket, &QTcpSocket::disconnected, this, &DataConnectionServer::on_socket_disconnect);
        QObject::connect(socket, &QTcpSocket::bytesWritten, this, &DataConnectionServer::on_socket_readywrite);
        write_json(socket, data_connected_message());
    }
 
    update_status();
}


void DataConnectionServer::on_socket_error(QAbstractSocket::SocketError error)
{
    QObject *id = QObject::sender();
    SocketState &state = d_connections.find(id).value();

    QString error_string = QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error);
    emit debug_message(error_string + " from " + state.socket->peerAddress().toString());
}


void DataConnectionServer::on_socket_readyread()
{
    QObject *id = QObject::sender();
    DataSocketState &state = d_connections.find(id).value();
    QJsonDocument doc = read(state.socket, state.incoming, state.buffer);

    while (!doc.isEmpty())
    {
        handle_message(doc, state);
        doc = read(state.socket, state.incoming, state.buffer);
    }
}


void DataConnectionServer::on_socket_readywrite([[maybe_unused]] uint16_t written)
{
    QObject *id = QObject::sender();
    DataSocketState &state = d_connections.find(id).value();
    activate(state);
}


void DataConnectionServer::on_socket_disconnect()
{
    QObject *id = QObject::sender();
    DataSocketState &state = d_connections.find(id).value();

    state.socket->deleteLater();
    d_connections.remove(id);
    update_status();
}