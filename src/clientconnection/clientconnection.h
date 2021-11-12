#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QtCore>
#include <QTcpSocket>

#include "../connectionemitter/connectionemitter.h"

class ClientConnection : public ConnectionEmitter
{
    Q_OBJECT

    QTcpSocket *d_connection;

    public:
        ClientConnection();
        ~ClientConnection();

        void connect(QString const &host, uint16_t port);

};

#endif