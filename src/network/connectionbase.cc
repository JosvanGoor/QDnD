#include "connectionbase.h"

////////////////////
//  Constructors  //
////////////////////

ConnectionBase::ConnectionBase(QObject *parent)
:   QObject(parent)
{ }


ConnectionBase::~ConnectionBase()
{ }


////////////////////
//    Dispatch    //
////////////////////

void ConnectionBase::signal_message(QJsonDocument const &doc, SocketState &state)
{
    QJsonObject obj = doc.object();
    MessageType type = static_cast<MessageType>(obj["type"].toInt());
    debug_message("Received " + as_string(type));

    switch (type)
    {
        case MessageType::WELCOME: break; // TODO: implement
        
        case MessageType::HANDSHAKE:
        {
            QString name = obj["name"].toString();
            QByteArray b64_avatar = obj["avatar"].toString().toLocal8Bit();
            QColor color = obj["color"].toString().toUInt(nullptr, 16);
            state.identifier = name;
            emit player_connected(name, b64_avatar, color);
        }
        break;

        case MessageType::DISCONNECTED:
            emit player_disconnected(obj["name"].toString());
        break;

        case MessageType::PING:
            send(pong_message());
        break;

        case MessageType::PONG: break;

        case MessageType::PIXMAP_TRANSFER:
            emit pixmap_tranfer(obj["name"].toString(), obj["data"].toString().toLocal8Bit());
        break;

        case MessageType::CHAT_MESSAGE:
            emit chat_message(obj["name"].toString(), obj["message"].toString());
        break;

        case MessageType::DISPLAY_UPDATE:
            emit display_updated(obj["name"].toString());
        break;

        case MessageType::DIEROLL_MESSSAGE:
            emit roll_performed(obj["name"].toString(), obj["expression"].toString(), obj["result"].toString());
        break;

        default:
            emit debug_message("Received unknown message type: " + as_string(type));
        break;
    }
}
