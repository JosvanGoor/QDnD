#include "messagebuilding.h"

////////////////////
//     System     //
////////////////////

QJsonDocument welcome_message()
{
    return {};
}


QJsonDocument handshake_message(QString const &name, QByteArray b64_avatar, QColor color)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::HANDSHAKE);
    obj["name"] = name;
    obj["avatar"] = QString(b64_avatar);
    obj["color"] = QString::number(color.rgb(), 16);
    return QJsonDocument{obj};
}


QJsonDocument ping_message()
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PING);
    return QJsonDocument{obj};
}


QJsonDocument pong_message()
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PONG);
    return QJsonDocument{obj};
}


////////////////////
//      Chat      //
////////////////////

QJsonDocument chat_message(QString const &name, QString const &message)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::CHAT_MESSAGE);
    obj["name"] = name;
    obj["message"] = message;
    return QJsonDocument{obj};
}
