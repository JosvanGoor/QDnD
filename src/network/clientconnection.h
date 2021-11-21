#ifndef NETWORK_CLIENTCONNECTION_H
#define NETWORK_CLIENTCONNECTION_H

#include <QHostAddress>
#include <QMetaEnum>

#include "connectionbase.h"

#include "../utility/networking.h"

class ClientConnection : public ConnectionBase
{
    Q_OBJECT

    SocketState d_socket_state;

    public:
        explicit ClientConnection(QObject *parent = nullptr);
        ~ClientConnection();

        void connect(QString const &host, uint16_t port);
        void disconnect() override;
        bool is_connected() override;
        bool is_server() override;

        void send(QJsonDocument const &doc, bool signal_self = false) override;

    protected slots:
        void on_connected();
        void on_socket_error(QAbstractSocket::SocketError error);
        void on_socket_readyread();

};

#endif