#include "clientconnection.h"

void ClientConnection::on_data()
{
    QJsonDocument doc = read_socket(d_connection, d_incoming, d_buffer);

    if (doc.isEmpty())
        return;

    if (doc["type"].toString() == "DISPLAY_UPDATE")
        display_update_message(doc);
    else if (doc["type"].toString() == "HANDSHAKE")
        new_connection(doc);
    else if (doc["type"].toString() == "USER_DISCONNECTED")
        user_disconnected(doc.object()["name"].toString());
    else if (doc["type"].toString() == "AVATAR_MOVED")
        avatar_move_message(doc["name"].toString(), {doc["x"].toInt(), doc["y"].toInt()});
    else if (doc["type"].toString() == "NEW_LINE")
        line_received(doc);
    else if (doc["type"].toString() == "LINE_REMOVED")
        line_removed(doc["name"].toString());
    else if (doc["type"].toString() == "MONSTER_REMOVED")
        token_removed(doc["name"].toString());
    else if (doc["type"].toString() == "MONSTER_ADDED")
        token_added(doc);
    else if (doc["type"].toString() == "PING")
    {
        send_blob(d_connection, "{\"type\": \"PONG\"}");
        debug_message("Ping! sent pong to host");
    }
}