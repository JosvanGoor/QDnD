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
    obj["color"] = QString::number(color.rgb(), 16);
    obj["scale"] = as_int(scale);
    return QJsonDocument{obj};
}


QJsonDocument player_connected_message(QString const &id, QString const &avatar_key, QColor const &color, GridScale scale)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PLAYER_CONNECTED);
    obj["id"] = id;
    obj["avatar"] = avatar_key;
    obj["color"] = QString::number(color.rgb(), 16);
    obj["scale"] = as_int(scale);
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