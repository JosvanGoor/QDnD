#include "messagebuilder.h"

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
//  Grid Control  //
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