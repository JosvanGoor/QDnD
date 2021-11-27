#ifndef NETWORK_SERVERCONNECTION_H
#define NETWORK_SERVERCONNECTION_H

#include <QMap>
#include <QMetaEnum>
#include <QTcpServer>
#include <QTimer>

#include "connectionbase.h"
#include "messagebuilder.h"

struct SocketState
{
    int incoming = 0;
    uint64_t ping_time = -1;
    QTcpSocket *socket = nullptr;
    QByteArray buffer;
};

class ServerConnection : public ConnectionBase
{
    Q_OBJECT

    QTimer d_ping_timer;
    QTcpServer *d_server;
    QMap<QObject*, SocketState> d_connections;

    public:
        explicit ServerConnection(QObject *parent = nullptr);
        ~ServerConnection();

        // io
        void dispatch(QByteArray const &data);
        void send(QByteArray const &data) override;
        void send(QJsonDocument const &doc) override;
        void connect(QString const &host, uint16_t port = 4144) override;
        void disconnect() override;

        // messages
        void pre_handle_message(QJsonDocument const &doc);

        // utility
        void update_status();

    private slots:
        // internal slots
        void on_ping_timer();
        void on_new_connection();
        void on_socket_error(QAbstractSocket::SocketError error);
        void on_socket_readyread();
        void on_socket_readywrite(uint64_t written);
        void on_socket_disconnect();
};

#endif