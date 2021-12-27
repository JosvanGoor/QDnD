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

        case MessageType::SYNCHRONIZE_LINES:
            emit line_sync(obj);
        break;

        case MessageType::SYNCHRONIZE_ENTITIES:
            emit synchronize_entities(obj);
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

        case MessageType::LINES_DELETED:
            emit lines_removed(obj);
        break;

        case MessageType::LINES_CLEARED:
            emit lines_cleared(obj["id"].toString());
        break;

        case MessageType::ENTITY_ADDED:
            emit entity_added(obj);
        break;

        case MessageType::ENTITIES_REMOVED:
            emit entities_removed(obj);
        break;

        case MessageType::ENTITIES_CLEARED:
            emit entities_cleared();
        break;

        case MessageType::ENTITIES_MOVED:
            emit entities_moved(obj);
        break;

        case MessageType::ENTITIES_ROTATED:
            emit entities_rotated(obj);
        break;

        case MessageType::GRID_GROUPS_CLEARED:
            emit clear_grid_groups();
        break;

        case MessageType::GRID_ITEM_REMOVED:
            emit grid_item_removed(obj["group"].toString(), obj["index"].toInt());
        break;

        case MessageType::GRID_ITEM_ADDED:
            emit grid_item_added(obj);
        break;

        case MessageType::GRID_GROUP_VISIBILITY:
            emit grid_group_visibility(obj["group"].toString(), static_cast<VisibilityMode>(obj["visibility"].toInt()));
        break;

        case MessageType::SYNCHRONIZE_GRID_GROUP:
            emit synchronize_grid_group(obj);
        break;

        default: break;
    }
}