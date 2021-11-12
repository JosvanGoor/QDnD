#include "hostconnection.h"

void HostConnection::start_listening(uint16_t port)
{
    d_server->listen(QHostAddress::Any, port);
    connection_status_update("Hosting @ " + QString::number(port) + " (0 connected)");
}


void HostConnection::on_incoming_connection()
{
    QTcpSocket *socket;
    while ((socket = d_server->nextPendingConnection()) != nullptr)
    {
        std::cout << "Connection!\n" << std::flush;
        d_clients.insert(socket);
        connection_status_update("Hosting @ " + QString::number(d_server->serverPort()) + " (" + QString::number(d_clients.size()) + " connected)");

        // todo: connect connection
    }
}