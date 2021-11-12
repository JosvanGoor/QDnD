#include "clientconnection.h"

ClientConnection::ClientConnection()
{
    d_connection = new QTcpSocket;
}


ClientConnection::~ClientConnection()
{
    delete d_connection;
}