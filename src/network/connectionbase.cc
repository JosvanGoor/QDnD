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
        }
        break;

        case MessageType::DISCONNECTED:
            player_disconnected(obj["name"].toString());
        break;

        default:
            debug_message("Received unknown message type: " + as_string(type));
        break;
    }
}