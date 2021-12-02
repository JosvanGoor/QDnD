#ifndef NETWORK_MESSAGEBUILDER_H
#define NETWORK_MESSAGEBUILDER_H

#include <QColor>
#include <QJsonArray>
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
QJsonDocument pixmap_request_message(QVector<QString> const &keys);
QJsonDocument pixmap_transfer_message(QString const &key, QByteArray const &b64_avatar);
QJsonDocument pixmap_not_found_message(QString const &key);

// simple
QJsonDocument chat_message(QString const &id, QString const &message);
QJsonDocument richtext_message(QString const &id, QString const &message);
QJsonDocument display_update_message(QString const &key);

#endif