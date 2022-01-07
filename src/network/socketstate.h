#ifndef NETWORK_SOCKETSTATE_H
#define NETWORK_SOCKETSTATE_H

#include <QByteArray>
#include <QString>
#include <QTcpSocket>
#include <QVector>

struct SocketState
{
    int incoming = 0;
    uint64_t ping_time = -1;
    QTcpSocket *socket = nullptr;
    QByteArray buffer;
    QString identifier;
};

struct DataSocketState : public SocketState
{
    QVector<QByteArray> queue;
};

#endif