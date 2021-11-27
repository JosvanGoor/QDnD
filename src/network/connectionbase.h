#ifndef NETWORK_CONNECTIONBASE_H
#define NETWORK_CONNECTIONBASE_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QTcpSocket>

#include "../utility/enums.h"

class ConnectionBase : public QObject
{
    Q_OBJECT

    public:
        explicit ConnectionBase(QObject *parent = nullptr);
        ~ConnectionBase();

        virtual void send(QByteArray const &data) = 0;
        virtual void send(QJsonDocument const &doc) = 0;
        virtual void connect(QString const &host, uint16_t port = 4144) = 0;
        virtual void disconnect() = 0;

    protected:
        // base IO
        void write_blob(QTcpSocket *socket, QByteArray const &data, bool limited);
        void write_json(QTcpSocket *socket, QJsonDocument const &doc, bool limited = true);
        QJsonDocument read(QTcpSocket *socket, int &incoming, QByteArray &buffer);

        // messages
        void handle_message(QJsonDocument const &doc);

    signals:
        // system
        void debug_message(QString const &message);
        void connection_status(QString const &status);

        // messages

};  

#endif