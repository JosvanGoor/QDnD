#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QtCore>
#include <QTcpSocket>

#include "../connectioncommon/connectioncommon.h"

class ClientConnection : public ConnectionCommon
{
    Q_OBJECT

    QTcpSocket *d_connection;

    public:
        ClientConnection();
        ~ClientConnection();

        void connect(QString const &host, uint16_t port);

};

#endif