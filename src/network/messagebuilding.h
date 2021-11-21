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

// chat
QJsonDocument chat_message(QString const &name, QString const &message);


#endif