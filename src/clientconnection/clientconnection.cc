#include "clientconnection.h"

ClientConnection::ClientConnection()
{
    d_connection = new QTcpSocket;
    d_incoming = 0;

    QObject::connect
    (
        d_connection,
        &QTcpSocket::readyRead,
        this,
        &ClientConnection::on_data
    );
}


ClientConnection::~ClientConnection()
{
    delete d_connection;
}