#ifndef NETWORK_SERVERCONNECTION_H
#define NETWORK_SERVERCONNECTION_H

#include <QMap>
#include <QMetaEnum>
#include <QTcpServer>
#include <QTimer>
#include <QPixmap>

#include "connectionbase.h"
#include "dataconnectionserver.h"
#include "messagebuilder.h"
#include "socketstate.h"
#include "../utility/loading.h"

class ServerConnection : public ConnectionBase
{
    Q_OBJECT

    QTimer d_ping_timer;
    QTcpServer *d_server;
    QMap<QObject*, SocketState> d_connections;
    DataConnectionServer *d_data_server;

    public:
        explicit ServerConnection(QObject *parent = nullptr);
        ~ServerConnection();

        // io
        void dispatch(QByteArray const &data, bool full_connections_only = false);
        void send(QByteArray const &data) override;
        void send(QJsonDocument const &doc) override;
        void connect(QString const &host, uint16_t port = 4144) override;
        void disconnect() override;

        // messages
        void pre_handle_message(QJsonDocument const &doc, SocketState &state);
        void message_to(QString const &identifier, QByteArray const &data);
        void message_to(QString const &identifier, QJsonDocument const &doc);
        void send_data_message(QString const &identifier, QJsonDocument const &doc);

        // utility
        bool is_server() override;
        void update_status();
        DataConnectionServer *data_server();

    private slots:
        // internal slots
        void on_ping_timer();
        void on_new_connection();
        void on_socket_error(QAbstractSocket::SocketError error);
        void on_socket_readyread();
        void on_socket_disconnect();

    signals:
        void dispatch_data(QJsonDocument const &doc);
        void dispatch_data_to(QString const &id, QJsonDocument const &doc);
};

#endif