#ifndef NETWORK_MESSAGEBUILDER_H
#define NETWORK_MESSAGEBUILDER_H

#include <QColor>
#include <QJsonDocument>
#include <QJsonObject>

#include "../utility/enums.h"

// system
QJsonDocument handshake_message(QString const &id, QByteArray const &b64_avatar, QColor const &color, GridScale scale);
QJsonDocument player_connected_message(QString const &id, QString const &avatar_key, QColor const &color, GridScale scale);
QJsonDocument player_disconnected_message(QString const &id);
QJsonDocument ping_message() noexcept;
QJsonDocument pong_message() noexcept;

// file transfer


// simple


#endif