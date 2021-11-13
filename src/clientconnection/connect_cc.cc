#include "clientconnection.h"

void ClientConnection::connect(QString const &host, uint16_t port)
{
    d_connection->connectToHost(host, port);
    connection_status_update("Connected to Host!");

    QByteArray data{"{\"name\": \"Bob\"}"};
    send_blob(d_connection, data);
}