#ifndef UTILITY_NETWORKING_H
#define UTILITY_NETWORKING_H

#include <QByteArray>
#include <QJsonDocument>
#include <QTcpSocket>

struct SocketState
{
    QTcpSocket *socket;
    QByteArray buffer;
    uint32_t incoming = 0;
    QString identifier = "";
};


void send_blob(QTcpSocket *socket, QByteArray const &blob, bool limited = true);
void send_json_blob(QTcpSocket *socket, QJsonDocument const &document, bool limited = true);
QJsonDocument read_connection(SocketState &state);

#endif