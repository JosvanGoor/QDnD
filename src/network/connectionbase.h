#ifndef NETWORK_CONNECTIONBASE_H
#define NETWORK_CONNECTIONBASE_H

#include <QObject>

class ConnectionBase : public QObject
{
    Q_OBJECT

    public:
        explicit ConnectionBase(QObject *parent = nullptr);
        ~ConnectionBase();

        virtual void disconnect() = 0;
        virtual bool is_connected() = 0;
        virtual bool is_server() = 0;
        virtual void send(QJsonDocument const &doc) = 0;

    signals:
        // general signals
        void debug_message(QString const &message);
        void chat_connection_message(QString const &message);
        void connection_status_update(QString const &state);
};

#endif