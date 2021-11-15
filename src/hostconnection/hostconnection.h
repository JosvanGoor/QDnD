#ifndef HOSTCONNECTION_H
#define HOSTCONNECTION_H

#include <QByteArray>
#include <QMap>
#include <QPixmap>
#include <QTcpServer>
#include <QTcpSocket>

#include "../connectioncommon/connectioncommon.h"

struct ConnectionState
{
    QString name;
    QPixmap avatar;
    QTcpSocket *d_socket;

    uint32_t incoming_size;
    QByteArray d_buffer;
};

class HostConnection : public ConnectionCommon
{
    Q_OBJECT

    QTcpServer *d_server;
    QMap<QObject*, ConnectionState> d_clients;

    public:
        HostConnection();
        ~HostConnection();

        void start_listening(uint16_t port);

        void dispatch(QJsonDocument const &doc);

    private slots:
        void on_incoming_data();
        void on_incoming_connection();
        void on_connection_closed();
};

#endif