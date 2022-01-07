#ifndef NETWORK_CLIENTCONNECTION_H
#define NETWORK_CLIENTCONNECTION_H

#include <QHostAddress>
#include <QMetaEnum>

#include "connectionbase.h"
#include "dataconnectionclient.h"

class ClientConnection : public ConnectionBase
{
    Q_OBJECT

    int d_incoming;
    QTcpSocket *d_socket;
    QByteArray d_buffer;
    DataConnectionClient *d_data_client;

    public:
        explicit ClientConnection(QObject *parent = nullptr);
        ~ClientConnection();

        bool is_server() override;
        DataConnectionClient *data_client();

        // io
        void send(QByteArray const &data) override;
        void send(QJsonDocument const &doc) override;
        void connect(QString const &host, uint16_t port = 4144) override;
        void disconnect() override;

        // internal slots
    private slots:
        void on_connected();
        void on_disconnected();
        void on_socket_error(QAbstractSocket::SocketError error);
        void on_socket_readyread();
};

#endif