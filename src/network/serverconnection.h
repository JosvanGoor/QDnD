#ifndef NETWORK_SERVERCONNECTION_H
#define NETWORK_SERVERCONNECTION_H

#include <QJsonObject>
#include <QMap>
#include <QMetaEnum>
#include <QTcpServer>
#include <QTimer>

#include "connectionbase.h"
#include "messagebuilding.h"
#include "messagetypes.h"
#include "../utility/networking.h"

class ServerConnection : public ConnectionBase
{
    Q_OBJECT

    QTimer d_ping_timer;
    QTcpServer *d_server;
    QMap<QObject*, SocketState> d_connections;
    SocketState d_self;

    public:
        explicit ServerConnection(QObject *parent = nullptr);
        ~ServerConnection();

        void start_listening(uint16_t port);
        void disconnect() override;
        bool is_connected() override;
        bool is_server() override;

        void send(QJsonDocument const &doc, bool signal_self = false) override;
        void update_status();

    protected slots:
        void on_ping_timer();
        void on_new_connection();
        void on_socket_error(QAbstractSocket::SocketError error);
        void on_socket_readyread();
        void on_socket_disconnected();
};

#endif