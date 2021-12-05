#ifndef NETWORK_CONNECTIONBASE_H
#define NETWORK_CONNECTIONBASE_H

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QPixmap>
#include <QTcpSocket>

#include "messagebuilder.h"
#include "../utility/enums.h"
#include "../utility/loading.h"

class ConnectionBase : public QObject
{
    Q_OBJECT

    public:
        explicit ConnectionBase(QObject *parent = nullptr);
        ~ConnectionBase();

        virtual bool is_server() = 0;

        virtual void send(QByteArray const &data) = 0;
        virtual void send(QJsonDocument const &doc) = 0;
        virtual void connect(QString const &host, uint16_t port = 4144) = 0;
        virtual void disconnect() = 0;

        // messages
        void handle_message(QJsonDocument const &doc);

    protected:
        // base IO
        void write_blob(QTcpSocket *socket, QByteArray const &data, bool limited);
        void write_json(QTcpSocket *socket, QJsonDocument const &doc, bool limited = true);
        QJsonDocument read(QTcpSocket *socket, int &incoming, QByteArray &buffer);

    signals:
        // system
        void debug_message(QString const &message);
        void connection_status(QString const &status);

        // maintenance
        void synchronization(QJsonObject const &object);
        void pixmap_received(QString const &key, QPixmap const &pixmap);
        void pixmap_requested(QString const &id, QString const &key);
        void display_update(QString const &key);

        // player stuff
        void player_joins(QJsonObject const &object);
        void player_leaves(QString const &identifier);
        void player_moved(QString const &id, QPoint const &pos);
        void chat_message(QString const &name, QString const &message);
        void richtext_message(QString const&name, QString const &message);

        // grid stuff
        void line_sync(QJsonObject const &obj);
        void line_received(QJsonObject const &obj);
        void lines_removed(QJsonObject const &obj);
        void lines_cleared(QString const &id);
};  

#endif