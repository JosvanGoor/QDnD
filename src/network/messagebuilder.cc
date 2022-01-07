#include "messagebuilder.h"

#include "../control/applicationcontrol.h" // because forward decl.

////////////////////
//     System     //
////////////////////

QJsonDocument handshake_message(QString const &id, QByteArray const &b64_avatar, QColor const &color, GridScale scale)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::HANDSHAKE);
    obj["id"] = id;
    obj["avatar"] = QString{b64_avatar};
    obj["color"] = static_cast<int>(color.rgba());
    obj["scale"] = as_int(scale);
    return QJsonDocument{obj};
}


QJsonDocument data_handshake_message(QString const &id)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::HANDSHAKE);
    obj["id"] = id;
    return QJsonDocument{obj};
}


QJsonDocument data_connected_message()
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::DATA_CONNECTED);
    return QJsonDocument{obj};
}


QJsonDocument synchronize_lines_message(QString const &id, QMap<QString, DrawLine> const &lines)
{
    QJsonArray line_objects;

    for (auto it = lines.begin(); it != lines.end(); ++it)
    {
        QJsonArray line;
        for (auto &pt : it.value().line)
        {
            QJsonObject obj;
            obj["x"] = pt.x1();
            obj["y"] = pt.y1();
            line.push_back(obj);
        }

        if (!it.value().line.isEmpty())
        {
            QJsonObject obj;
            obj["x"] = it.value().line.back().x2();
            obj["y"] = it.value().line.back().y2();
            line.push_back(obj);
        }

        QJsonObject obj;
        obj["name"] = it.key();
        obj["color"] = static_cast<int>(it.value().color.rgba());
        obj["points"] = line;
        line_objects.push_back(obj);
    }

    QJsonObject obj;
    obj["type"] = as_int(MessageType::SYNCHRONIZE_LINES);
    obj["id"] = id;
    obj["lines"] = line_objects;
    return QJsonDocument{obj};
}


QJsonDocument synchronize_entities_message(QMap<QString, Entity> const &entities)
{
    QJsonArray arr;
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        QJsonObject obj;
        obj["name"] = it.key();
        obj["avatar"] = it.value().avatar();
        obj["x"] = it.value().position().x();
        obj["y"] = it.value().position().y();
        obj["scale"] = as_int(it.value().scale());
        obj["rotation"] = it.value().rotation();
        arr.push_back(obj);
    }

    QJsonObject obj;
    obj["type"] = as_int(MessageType::SYNCHRONIZE_ENTITIES);
    obj["entities"] = arr;
    return QJsonDocument{obj};
}


QJsonDocument synchronize_grid_group_message(GridItemGroup const &group)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::SYNCHRONIZE_GRID_GROUP);
    obj["group"] = group.serialize(false);
    return QJsonDocument{obj};
}


QJsonDocument player_connected_message(QString const &id, QString const &avatar_key, QColor const &color, GridScale scale)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PLAYER_CONNECTED);
    obj["id"] = id;
    obj["avatar"] = avatar_key;
    obj["color"] = static_cast<int>(color.rgba());
    obj["scale"] = as_int(scale);
    obj["x"] = 0;
    obj["y"] = 0;
    return QJsonDocument{obj};
}


QJsonDocument player_disconnected_message(QString const &id)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PLAYER_DISCONNECTED);
    obj["id"] = id;
    return QJsonDocument{obj};
}


QJsonDocument ping_message() noexcept
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PING);
    return QJsonDocument{obj};
}


QJsonDocument pong_message() noexcept
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PONG);
    return QJsonDocument{obj};
}


////////////////////
// File Transfer  //
////////////////////

QJsonDocument pixmap_request_message(QVector<QString> const &keys)
{
    QJsonArray requests;
    for (auto const &str : keys)
        requests.push_back(str);

    QJsonObject obj;
    obj["type"] = as_int(MessageType::PIXMAP_REQUEST);
    obj["requests"] = requests;
    return QJsonDocument{obj};
}


QJsonDocument pixmap_transfer_message(QString const &key, QByteArray const &b64_data)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PIXMAP_TRANSFER);
    obj["key"] = key;
    obj["data"] = QString{b64_data};
    return QJsonDocument{obj};
}


QJsonDocument pixmap_not_found_message(QString const &key)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PIXMAP_NOT_FOUND);
    obj["key"] = key;
    return QJsonDocument{obj};
}


////////////////////
//  Chat / Text   //
////////////////////

QJsonDocument chat_message(QString const &id, QString const &message)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::CHAT);
    obj["id"] = id;
    obj["message"] = message;
    return QJsonDocument{obj};
}


QJsonDocument richtext_message(QString const &id, QString const &message)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::RICH_TEXT);
    obj["id"] = id;
    obj["message"] = message;
    return QJsonDocument{obj};
}


QJsonDocument display_update_message(QString const &key)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::DISPLAY_UPDATE);
    obj["key"] = key;
    return QJsonDocument{obj};
}


////////////////////
//    Entities    //
////////////////////

QJsonDocument player_move_message(QString const &id, QPoint const &newpos)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PLAYER_MOVED);
    obj["id"] = id;
    obj["x"] = newpos.x();
    obj["y"] = newpos.y();
    return QJsonDocument{obj};
}


QJsonDocument player_entity_added_message(QString const &id, QByteArray const &b64_img, QPoint const &position, GridScale size)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PLAYER_ENTITY_ADDED);
    obj["name"] = id;
    obj["avatar"] = QString{b64_img};
    obj["x"] = position.x();
    obj["y"] = position.y();
    obj["scale"] = as_int(size);
    return QJsonDocument{obj};
}


QJsonDocument entity_added_message(QString const &name, QString const &avatar_key, QPoint const &position, GridScale scale)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::ENTITY_ADDED);
    obj["name"] = name;
    obj["avatar"] = avatar_key;
    obj["x"] = position.x();
    obj["y"] = position.y();
    obj["scale"] = as_int(scale);
    return QJsonDocument{obj};
}


QJsonDocument entities_moved_message(QSet<QString> const &names, QPoint const &newpos)
{
    QJsonArray arr;
    for (auto &name : names)
        arr.push_back(name);

    QJsonObject obj;
    obj["type"] = as_int(MessageType::ENTITIES_MOVED);
    obj["entities"] = arr;
    obj["x"] = newpos.x();
    obj["y"] = newpos.y();
    return QJsonDocument{obj};
}


QJsonDocument entities_removed_message(QVector<QString> const &names)
{
    QJsonArray arr;
    for (auto &name : names)
        arr.push_back(name);

    QJsonObject obj;
    obj["type"] = as_int(MessageType::ENTITIES_REMOVED);
    obj["entities"] = arr;
    return QJsonDocument{obj};
}


QJsonDocument entities_cleared_message()
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::ENTITIES_CLEARED);
    return QJsonDocument{obj};
}


QJsonDocument entities_rotated_message(QSet<QString> const &entities, int angle)
{
    QJsonArray arr;
    for (auto &name : entities)
        arr.push_back(name);

    QJsonObject obj;
    obj["type"] = as_int(MessageType::ENTITIES_ROTATED);
    obj["entities"] = arr;
    obj["angle"] = angle;
    return QJsonDocument{obj};
}


////////////////////
//   Grid Items   //
////////////////////

QJsonDocument grid_groups_cleared_message()
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::GRID_GROUPS_CLEARED);
    return QJsonDocument{obj};
}


QJsonDocument grid_item_added_message(QString const &group, GridItem const &item)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::GRID_ITEM_ADDED);
    obj["group"] = group;
    obj["pixmap_code"] = item.pixmap_code;
    obj["x"] = item.position.x();
    obj["y"] = item.position.y();
    obj["rotation"] = item.rotation;
    obj["scale"] = as_int(item.scale);
    obj["visibility"] = as_int(item.visibility);
    return QJsonDocument{obj};
}


QJsonDocument grid_item_removed_message(QString const &group, int index)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::GRID_ITEM_REMOVED);
    obj["group"] = group;
    obj["index"] = index;
    return QJsonDocument{obj};
}


QJsonDocument grid_group_removed_message(QString const &group)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::GRID_GROUP_REMOVED);
    obj["group"] = group;
    return QJsonDocument{obj};
}


QJsonDocument grid_group_visibility_message(QString const &group, VisibilityMode mode)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::GRID_GROUP_VISIBILITY);
    obj["group"] = group;
    obj["visibility"] = as_int(mode);
    return QJsonDocument{obj};
}


////////////////////
//  Line Control  //
////////////////////

QJsonDocument line_drawn_message(QString const &id, QString const &name, QVector<QLine> const &lines, QColor const &color)
{
    QJsonArray line_arr;
    
    for (auto &bit : lines)
    {
        QJsonObject obj;
        obj["x"] = bit.x1();
        obj["y"] = bit.y1();
        line_arr.push_back(obj);
    }

    if (!lines.isEmpty())
    {
        QJsonObject obj;
        obj["x"] = lines.back().x2();
        obj["y"] = lines.back().y2();
        line_arr.push_back(obj);
    }

    QJsonObject obj;
    obj["type"] = as_int(MessageType::LINE_DRAWN);
    obj["id"] = id;
    obj["name"] = name;
    obj["color"] = static_cast<int>(color.rgba());
    obj["points"] = line_arr;
    return QJsonDocument{obj};
}


QJsonDocument lines_removal_message(QString const &id, QVector<QString> const &names)
{
    QJsonArray arr;
    for (auto &line_id : names)
        arr.push_back(line_id);

    QJsonObject obj;
    obj["type"] = as_int(MessageType::LINES_DELETED);
    obj["id"] = id;
    obj["lines"] = arr;
    return QJsonDocument{obj};
}


QJsonDocument lines_cleared_message(QString const &id)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::LINES_CLEARED);
    obj["id"] = id;
    return QJsonDocument{obj};
}
