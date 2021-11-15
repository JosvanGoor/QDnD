#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QtCore>
#include <QTcpSocket>

#include "../connectioncommon/connectioncommon.h"

class ClientConnection : public ConnectionCommon
{
    Q_OBJECT

    uint32_t d_incoming;
    QTcpSocket *d_connection;
    QByteArray d_buffer;

    public:
        ClientConnection();
        ~ClientConnection();

        void send(QString const &data);
        void connect(QString const &host, uint16_t port);

        void on_data();

};

#endif