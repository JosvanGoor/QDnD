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
        
        // network messages
        void display_update_message(QJsonDocument const &doc);
        void new_connection(QJsonDocument const &doc);
        void user_disconnected(QString const &name);
        void avatar_move_message(QString const &name, QPoint const &pos);
        void line_received(QJsonDocument const &doc);
        void line_removed(QString const &name);

        void token_removed(QString const &name);
        void token_added(QJsonDocument const &doc);
};

#endif