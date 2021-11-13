#include "hostconnection.cc"

void HostConnection::on_connection_closed()
{
    QObject *sender = QObject::sender();


    if (auto it = d_clients.find(sender); it != d_clients.end())
    {
        it.value().d_socket->deleteLater();
        d_clients.erase(it);
    }

    connection_status_update("Hosting @ " + QString::number(d_server->serverPort()) + " (" + QString::number(d_clients.size()) + " connected)");
}