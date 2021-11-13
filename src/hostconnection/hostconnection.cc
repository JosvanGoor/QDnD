#include "hostconnection.h"

HostConnection::HostConnection()
{
    d_server = new QTcpServer;

    QObject::connect
    (
        d_server,
        &QTcpServer::newConnection,
        this,
        &HostConnection::on_incoming_connection
    );
}


HostConnection::~HostConnection()
{
    for (auto sock : d_clients)
        delete sock.d_socket;
    delete d_server;
}