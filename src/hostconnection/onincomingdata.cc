#include "hostconnection.h"

void HostConnection::on_incoming_data()
{
    QObject *sender = QObject::sender();
    std::cout << "Sender: " << static_cast<void*>(sender) << "\n" << std::flush;

    if (auto it = d_clients.find(sender); it != d_clients.end())
    {
        ConnectionState &conn = it.value();
        QJsonDocument doc = read_socket(conn.d_socket, conn.incoming_size, conn.d_buffer);
        if (doc.isEmpty())
            return;

        if (doc["type"].toString() == "HANDSHAKE")
        {
            conn.name = doc["name"].toString();
            conn.raw_avatar = QByteArray::fromBase64(doc["data"].toString().toLocal8Bit());
            conn.avatar.loadFromData(conn.raw_avatar);

            dispatch(doc);
            new_connection(doc);
        }
        else if (doc["type"].toString() == "AVATAR_MOVED")
        {
            dispatch(doc);
            avatar_move_message(doc["name"].toString(), {doc["x"].toInt(), doc["y"].toInt()});
        }
        else if (doc["type"].toString() == "NEW_LINE")
        {
            dispatch(doc);
            line_received(doc);
        }
        else if (doc["type"].toString() == "LINE_REMOVED")
        {
            dispatch(doc);
            line_removed(doc["name"].toString());
        }
        else if (doc["type"].toString() == "PONG")
        {
            debug_message("Pong from " + conn.d_socket->peerAddress().toString());
        }
    }
    else
        emit debug_message("Connection not found frowny face");
}