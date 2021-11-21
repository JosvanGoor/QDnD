#ifndef NETWORK_MESSAGEBUILDING_H
#define NETWORK_MESSAGEBUILDING_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "messagetypes.h"

// system
QJsonDocument welcome_message();
QJsonDocument handshake_message(QString const &name, QByteArray b64_avatar, QColor color = Qt::black);
QJsonDocument disconnect_message(QString const &name);
QJsonDocument ping_message();
QJsonDocument pong_message();

// transfer
QJsonDocument pixmap_request(QVector<QString> const &ids);
QJsonDocument pixmap_transfer(QString const &id, QByteArray const &b64_pixmap);
QJsonDocument pixmap_not_found(QString const &id);

// Simple
QJsonDocument chat_message(QString const &name, QString const &message);
QJsonDocument display_update(QString const &file_id);
QJsonDocument roll_message(QString const &name, QString const &expression, QString const &result);


#endif