#ifndef NETWORK_CLIENTCONNECTION_H
#define NETWORK_CLIENTCONNECTION_H

#include "connectionbase.h"

class ClientConnection : public ConnectionBase
{
    Q_OBJECT

    int d_incoming;
    QTcpSocket *d_socket;
    QByteArray d_buffer;

    public:
        explicit ClientConnection(QObject *parent = nullptr);
        ~ClientConnection();

        // io
        void send(QByteArray const &data) override;
        void send(QJsonDocument const &doc) override;
        void connect(QString const &host, uint16_t port = 4144) override;
        void disconnect() override;
};

#endif