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

    switch (type)
    {
        case MessageType::WELCOME: break; // TODO: implement
        
        case MessageType::HANDSHAKE:
        {
            QString name = obj["name"].toString();
            QByteArray b64_avatar = obj["avatar"].toString().toLocal8Bit();
            QColor color = obj["color"].toString().toUInt(nullptr, 16);
            state.identifier = name;
            player_connected(name, b64_avatar, color);
            chat_connection_message(name + " has connected.");
        }
        break;

        case MessageType::DISCONNECTED:
            player_disconnected(obj["name"].toString());
            chat_connection_message(obj["name"].toString() + " has been disconnected.");
        break;

        case MessageType::PING:
            send(pong_message());
        break;

        case MessageType::PONG:
            debug_message("Pong received!");
        break;

        case MessageType::CHAT_MESSAGE:
            chat_message(obj["name"].toString(), obj["message"].toString());
        break;

        default:
            debug_message("Received unknown message type: " + as_string(type));
        break;
    }
}