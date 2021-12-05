#include "connectionbase.h"

////////////////////
//  Constructor   //
////////////////////

ConnectionBase::ConnectionBase(QObject *parent)
:   QObject(parent)
{ }


ConnectionBase::~ConnectionBase()
{ }


////////////////////
//    Base IO     //
////////////////////

void ConnectionBase::write_blob(QTcpSocket *socket, QByteArray const &data, bool limited)
{
    uint32_t size = data.size();

    if (limited && size > 1'000'000) // over 1 MB
    {
        debug_message("ConnectionBase error: Blob's over 1MB will not be sent.");
        return;
    }

    if (size == 0)
        return;

    socket->write(reinterpret_cast<char*>(&size), sizeof(size));
    socket->write(data);
}


void ConnectionBase::write_json(QTcpSocket *socket, QJsonDocument const &doc, bool limited)
{
    QByteArray data = doc.toJson();
    write_blob(socket, data, limited);
}


QJsonDocument ConnectionBase::read(QTcpSocket *socket, int &incoming, QByteArray &buffer)
{
    QJsonDocument doc;
    buffer.append(socket->readAll());

    // didnt even read header yet.
    if (incoming == 0 && buffer.size() < 4)
        return doc;

    // read header
    if (incoming == 0)
    {
        incoming = *reinterpret_cast<uint32_t*>(buffer.data());
        buffer.remove(0, sizeof(uint32_t));
    }

    // parse payload, and reset state
    if (buffer.size() >= incoming)
    {
        doc = QJsonDocument::fromJson(buffer.left(incoming));
        buffer.remove(0, incoming);
        incoming = 0;

        return doc;
    }

    // payload not complete yet
    return doc;
}


////////////////////
//    Messages    //
////////////////////

void ConnectionBase::handle_message(QJsonDocument const &doc)
{
    QJsonObject obj = doc.object();
    MessageType type = static_cast<MessageType>(obj["type"].toInt());
    debug_message("ConnectionBase::handle_message [[" + as_string(type) + "]].");

    /*
        Client->Server only messages omitted here:
        HANDSHAKE, PIXMAP_REQUESTED
    */
    switch(type)
    {
        case MessageType::SYNCHRONIZE:
        {
            QJsonArray players = obj["players"].toArray();
            for (auto player : players)
                emit player_joins(player.toObject());
        }
        break;

        case MessageType::PLAYER_CONNECTED:
            emit player_joins(obj);
        break;

        case MessageType::PLAYER_DISCONNECTED:
            emit player_leaves(obj["id"].toString());
        break;

        case MessageType::PING:
            send(pong_message());
        break;        

        case MessageType::PIXMAP_TRANSFER:
        {
            QPixmap avatar = pixmap_from_b64(obj["data"].toString().toLocal8Bit());
            QString key = obj["key"].toString();
            emit debug_message("pixmap received: " + key);
            emit pixmap_received(key, avatar);
        }
        break;

        case MessageType::CHAT:
            emit chat_message(obj["id"].toString(), obj["message"].toString());
        break;

        case MessageType::RICH_TEXT:
            emit richtext_message(obj["id"].toString(), obj["message"].toString());
        break;

        case MessageType::DISPLAY_UPDATE:
            emit display_update(obj["key"].toString());
        break;

        case MessageType::PLAYER_MOVED:
            emit player_moved(obj["id"].toString(), {obj["x"].toInt(), obj["y"].toInt()});
        break;

        case MessageType::LINE_DRAWN:
            emit line_received(obj);
        break;

        default: break;
    }
}