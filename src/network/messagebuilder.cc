#include "messagebuilder.h"

////////////////////
//     System     //
////////////////////

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
