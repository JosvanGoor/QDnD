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


QJsonDocument disconnect_message(QString const &name)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::DISCONNECTED);
    obj["name"] = name;
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
//    Transfer    //
////////////////////

QJsonDocument pixmap_request(QVector<QString> const &ids)
{
    QJsonArray arr;
    for (auto &id : ids)
        arr.push_back(id);
    
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PIXMAP_REQUEST);
    obj["requests"] = arr;
    return QJsonDocument{obj};
}


QJsonDocument pixmap_transfer(QString const &id, QByteArray const &b64_pixmap)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PIXMAP_TRANSFER);
    obj["name"] = id;
    obj["data"] = QString{b64_pixmap};
    return QJsonDocument{obj};
}


QJsonDocument pixmap_not_found(QString const &id)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::PIXMAP_NOT_FOUND);
    obj["name"] = id;
    return QJsonDocument{obj};
}


////////////////////
//     Simple     //
////////////////////

QJsonDocument chat_message(QString const &name, QString const &message)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::CHAT_MESSAGE);
    obj["name"] = name;
    obj["message"] = message;
    return QJsonDocument{obj};
}


QJsonDocument display_update(QString const &fileid)
{
    QJsonObject obj;
    obj["type"] = as_int(MessageType::DISPLAY_UPDATE);
    obj["name"] = fileid;
    return QJsonDocument{obj};
}