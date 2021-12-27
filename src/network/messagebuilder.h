#ifndef NETWORK_MESSAGEBUILDER_H
#define NETWORK_MESSAGEBUILDER_H

#include <QColor>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLine>
#include <QPoint>
#include <QSet>

#include "../model/griditemgroup.h"
#include "../model/player.h"
#include "../utility/enums.h"

struct Entity; // forward decl temporary

// system
QJsonDocument handshake_message(QString const &id, QByteArray const &b64_avatar, QColor const &color, GridScale scale);
QJsonDocument synchronize_lines_message(QString const &id, QMap<QString, DrawLine> const &lines);
QJsonDocument synchronize_entities_message(QMap<QString, Entity> const &entities);
QJsonDocument synchronize_grid_group_message(GridItemGroup const &group);
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

// entity control
QJsonDocument player_move_message(QString const &id, QPoint const &newpos);
QJsonDocument player_entity_added_message(QString const &id, QByteArray const &b64_img, QPoint const &position, GridScale size);
QJsonDocument entity_added_message(QString const &id, QString const &avatar_key, QPoint const &position, GridScale size);
QJsonDocument entities_moved_message(QSet<QString> const &names, QPoint const &newpos);
QJsonDocument entities_removed_message(QVector<QString> const &names);
QJsonDocument entities_cleared_message();
QJsonDocument entities_rotated_message(QSet<QString> const &names, int angle);

// grid items
QJsonDocument grid_groups_cleared_message();
QJsonDocument grid_item_added_message(QString const &group, GridItem const &item);
QJsonDocument grid_group_visibility_message(QString const &group, VisibilityMode mode);

// lines
QJsonDocument line_drawn_message(QString const &id, QString const &name, QVector<QLine> const &lines, QColor const &color);
QJsonDocument lines_removal_message(QString const &id, QVector<QString> const &lines);
QJsonDocument lines_cleared_message(QString const &id);

#endif