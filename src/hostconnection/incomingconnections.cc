#include "hostconnection.h"

void HostConnection::start_listening(uint16_t port)
{
    if (!d_server->listen(QHostAddress::Any, port))
    {
        debug_message("Setting up host failed.");
        delete d_server;
        d_server = nullptr;
        return;
    }
    connection_status_update("Hosting @ " + QString::number(port) + " (0 connected)");
}


void HostConnection::on_incoming_connection()
{
    QTcpSocket *socket;
    while ((socket = d_server->nextPendingConnection()) != nullptr)
    {
        QVector<QJsonDocument> existing_users;
        for (auto &it : d_clients)
        {
            QJsonObject obj;
            obj["type"] = "HANDSHAKE";
            obj["name"] = it.name;
            obj["data"] = QString(it.raw_avatar.toBase64());
            existing_users.push_back(QJsonDocument{obj});
        }


        d_clients[socket] = {"", {}, {}, socket, 0, {}};
        debug_message("Host: New connection!");
        connection_status_update("Hosting @ " + QString::number(d_server->serverPort()) + " (" + QString::number(d_clients.size()) + " connected)");

        // connect new connection
        QObject::connect
        (
            socket,
            &QTcpSocket::readyRead,
            this,
            &HostConnection::on_incoming_data
        );

        QObject::connect
        (
            socket,
            &QTcpSocket::disconnected,
            this,
            &HostConnection::on_connection_closed
        );

        for (auto &it : existing_users)
        {
            send_blob(socket, it.toJson());
        }

    }
}
