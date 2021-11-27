#include "clientconnection.h"

////////////////////
//  Constructor   //
////////////////////

ClientConnection::ClientConnection(QObject *parent)
:   ConnectionBase(parent)
{
    d_incoming = 0;
    d_socket = new QTcpSocket;
}


ClientConnection::~ClientConnection()
{
    d_socket->deleteLater();
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