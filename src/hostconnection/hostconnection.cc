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

    QObject::connect(&d_ping_timer, &QTimer::timeout, this, &HostConnection::on_ping_timer);
}


HostConnection::~HostConnection()
{
    for (auto sock : d_clients)
        delete sock.d_socket;
    delete d_server;
}


void HostConnection::on_ping_timer()
{
    QJsonObject obj;
    obj["type"] = "PING";
    dispatch(QJsonDocument{obj});
    debug_message("Sent ping.");
}