#ifndef NETWORK_DATACONNECTIONCLIENT_H
#define NETWORK_DATACONNECTIONCLIENT_H

#include <QByteArray>
#include <QHostAddress>
#include <QMetaEnum>
#include <QTcpSocket>

#include "dataconnectionbase.h"
#include "messagebuilder.h"

class DataConnectionClient : public DataConnectionBase
{
    Q_OBJECT

    int d_incoming;
    QTcpSocket *d_socket;
    QByteArray d_buffer;

    uint16_t d_port;
    QString d_host;
    QString d_identifier;

    public:
        explicit DataConnectionClient(QObject *parent = nullptr);
        ~DataConnectionClient();

        // virtuals
        virtual bool is_server() const noexcept override;
        virtual void queue(QJsonDocument const &doc) override;
        virtual void connect(QString const &id, QString const &str, uint16_t port = 41201) override;
        virtual void disconnect() override;

        // thread main
        void run() override;

        // handle protocol
        void handle_message(QJsonDocument const &doc); // ping/pong

    private slots:
        void on_connected();
        void on_disconnected();
        void on_socket_error(QAbstractSocket::SocketError error);
        void on_socket_readyread();

    signals:
        void handshake_complete();
};

#endif