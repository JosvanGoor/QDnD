#ifndef CONNECTIONEMITTER_H
#define CONNECTIONEMITTER_H

#include <QtCore>
#include <QJsonDocument>
#include <QString>
#include <QTcpSocket>

#include <iostream> //_DBG

class ConnectionCommon : public QObject
{
    Q_OBJECT

    public:
        void send_blob(QTcpSocket *sock, QByteArray const &data);
        QJsonDocument read_socket(QTcpSocket *sock, uint32_t &incoming, QByteArray &buffer);

    signals:
        void debug_message(QString const &str);
        void connection_status_update(QString const &str);
};

#endif