#include "clientconnection.h"

void ClientConnection::send(QString const &data)
{
    send_blob(d_connection, data.toLocal8Bit());
}


void ClientConnection::connect(QString const &host, uint16_t port)
{
    d_connection->connectToHost(host, port);
    connection_status_update("Connected to Host!");
}