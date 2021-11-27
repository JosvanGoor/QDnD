#ifndef UTILITY_NETWORKING_H
#define UTILITY_NETWORKING_H

#include <QByteArray>
#include <QColor>
#include <QJsonDocument>
#include <QTcpSocket>
#include <QVector>

struct SocketState
{
    QTcpSocket *socket;
    QByteArray buffer;
    int incoming = 0;
    QColor color = Qt::black;
    QString avatar_key = "";
    QString identifier = "";
    QVector<QString> file_queue;
};


void send_blob(QTcpSocket *socket, QByteArray const &blob, bool limited = true);
void send_json_blob(QTcpSocket *socket, QJsonDocument const &document, bool limited = true);
QJsonDocument read_connection(SocketState &state);

#endif