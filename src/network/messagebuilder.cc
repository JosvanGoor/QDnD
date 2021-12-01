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
