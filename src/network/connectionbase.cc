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
        case MessageType::WELCOME:
            // TODO: WELCOME
        break;

        case MessageType::DISCONNECTED:
            // TODO: DISCONNECTED
        break;

        case MessageType::PING:
            // TODO: PING
        break;        

        case MessageType::PIXMAP_TRANSFER:
            // TODO: PIXMAP_TRANSFER
        break;

        case MessageType::CHAT_MESSAGE:
            // TODO: CHAT_MESSAGE
        break;

        case MessageType::DIEROLL_MESSSAGE:
            // TODO: DIEROLL_MESSAGE
        break;

        case MessageType::DISPLAY_UPDATE:
            // TODO: DISPLAY_UPDATE
        break;

        default: break;
    }
}