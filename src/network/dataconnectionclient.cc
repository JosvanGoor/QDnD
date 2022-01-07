#include "dataconnectionclient.h"

////////////////////
//  Constructor   //
////////////////////

DataConnectionClient::DataConnectionClient(QObject *parent)
:   DataConnectionBase(parent)
{
    d_incoming = 0;
    d_socket = new QTcpSocket;

    QObject::connect(d_socket, &QTcpSocket::connected, this, &DataConnectionClient::on_connected);
    QObject::connect(d_socket, &QTcpSocket::disconnected, this, &DataConnectionClient::on_disconnected);
    QObject::connect(d_socket, &QTcpSocket::errorOccurred, this, &DataConnectionClient::on_socket_error);
    QObject::connect(d_socket, &QTcpSocket::readyRead, this, &DataConnectionClient::on_socket_readyread);
}


DataConnectionClient::~DataConnectionClient()
{
    //
}


////////////////////
//    Virtuals    //
////////////////////

bool DataConnectionClient::is_server() const noexcept
{
    return false;
}


void DataConnectionClient::queue(QJsonDocument const &doc)
{
    write_json(d_socket, doc);
}


void DataConnectionClient::connect(QString const &id, QString const &host, uint16_t port)
{
    d_port = port;
    d_host = host;
    d_identifier = id;
}


void DataConnectionClient::disconnect()
{
    quit();
}


////////////////////
//  Thread Main   //
////////////////////

void DataConnectionClient::run()
{
    // connect
    d_socket->connectToHost(d_host, 41201);
    write_json(d_socket, data_handshake_message(d_identifier));
    
    exec();

    d_socket->disconnect();
    d_socket->deleteLater();
    d_socket = nullptr;
    // emit connection_status("No Connection");
}


////////////////////
//   Handle msg   //
////////////////////

void DataConnectionClient::handle_message(QJsonDocument const &doc)
{
    MessageType type = static_cast<MessageType>(doc["type"].toInt());
    debug_message("DataConnectionClient::handle_message [[" + as_string(type) + "]]");

    switch (type)
    {
        case MessageType::DATA_CONNECTED:
            emit handshake_complete();
        return;

        case MessageType::PING:
            queue(pong_message());
        return;

        default: break;
    }

    emit message_received(doc);
}


////////////////////
// Internal Slots //
////////////////////

void DataConnectionClient::on_connected()
{
    emit connection_status("Connected to " + d_socket->peerAddress().toString());
}


void DataConnectionClient::on_disconnected()
{
    emit connection_status("No connection");
}


void DataConnectionClient::on_socket_error(QAbstractSocket::SocketError error)
{
    QString error_string = QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error);
    emit debug_message("DataConnectionClient: " + error_string);
}


void DataConnectionClient::on_socket_readyread()
{
    debug_message("Receiving data");
    QJsonDocument doc = read(d_socket, d_incoming, d_buffer);

    while (!doc.isEmpty())
    {
        handle_message(doc);
        doc = read(d_socket, d_incoming, d_buffer);
    }
}