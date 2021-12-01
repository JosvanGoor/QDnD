#include "clientconnection.h"

////////////////////
//  Constructor   //
////////////////////

ClientConnection::ClientConnection(QObject *parent)
:   ConnectionBase(parent)
{
    d_incoming = 0;
    d_socket = new QTcpSocket;

    QObject::connect(d_socket, &QTcpSocket::connected, this, &ClientConnection::on_connected);
    QObject::connect(d_socket, &QTcpSocket::disconnected, this, &ClientConnection::on_disconnected);
    QObject::connect(d_socket, &QTcpSocket::errorOccurred, this, &ClientConnection::on_socket_error);
    QObject::connect(d_socket, &QTcpSocket::readyRead, this, &ClientConnection::on_socket_readyread);
}


ClientConnection::~ClientConnection()
{
    d_socket->deleteLater();
}


bool ClientConnection::is_server()
{
    return false;
}


////////////////////
//       IO       //
////////////////////

void ClientConnection::send(QByteArray const &data)
{
    write_blob(d_socket, data, true);
}


void ClientConnection::send(QJsonDocument const &doc)
{
    write_json(d_socket, doc);
}


void ClientConnection::connect(QString const &host, uint16_t port)
{
    d_socket->connectToHost(host, port);
}


void ClientConnection::disconnect()
{
    d_socket->close();
    emit connection_status("No connection");
}


////////////////////
// Internal Slots //
////////////////////

void ClientConnection::on_connected()
{
    connection_status("Connected to " + d_socket->peerAddress().toString());
}


void ClientConnection::on_disconnected()
{
    connection_status("No connection");
}


void ClientConnection::on_socket_error(QAbstractSocket::SocketError error)
{
    QString error_string = QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error);
    emit debug_message("ClientConnectionError: " + error_string);
}


void ClientConnection::on_socket_readyread()
{
    QJsonDocument doc = read(d_socket, d_incoming, d_buffer);

    while (!doc.isEmpty())
    {
        handle_message(doc);
        doc = read(d_socket, d_incoming, d_buffer);
    }
}