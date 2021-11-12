#ifndef HOSTCONNECTION_H
#define HOSTCONNECTION_H

#include <QSet>
#include <QTcpServer>
#include <QTcpSocket>

#include "../connectionemitter/connectionemitter.h"

class HostConnection : public ConnectionEmitter
{
    Q_OBJECT

    QTcpServer *d_server;
    QSet<QTcpSocket*> d_clients;

    public:
        HostConnection();
        ~HostConnection();

        void start_listening(uint16_t port);

    private:
        void on_incoming_connection();
};

#endif