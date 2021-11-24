#ifndef NETWORK_CONNECTIONBASE_H
#define NETWORK_CONNECTIONBASE_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

#include "messagebuilding.h"
#include "../utility/enums.h"
#include "../utility/networking.h"

class ConnectionBase : public QObject
{
    Q_OBJECT

    public:
        explicit ConnectionBase(QObject *parent = nullptr);
        ~ConnectionBase();

        virtual void disconnect() = 0;
        virtual bool is_connected() = 0;
        virtual bool is_server() = 0;
        virtual void send(QJsonDocument const &doc, bool signal_self = false) = 0;

        // dispatch
        void signal_message(QJsonDocument const &doc, SocketState &state);

    signals:
        // general signals
        void debug_message(QString const &message);
        void connection_status_update(QString const &state);

        // display
        void display_updated(QString const &id);
        void pixmap_tranfer(QString const &name, QByteArray const &b64_pixmap);

        // connect / disconnect
        void player_disconnected(QString const &name);
        void player_connected(QString const &name, QByteArray const &b64_avatar, QColor const &color);
        void chat_message(QString const &name, QString const &message);
        void roll_performed(QString const &name, QString const &expression, QString const &result);
};

#endif