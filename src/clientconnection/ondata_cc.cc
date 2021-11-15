#include "clientconnection.h"

void ClientConnection::on_data()
{
    QJsonDocument doc = read_socket(d_connection, d_incoming, d_buffer);

    if (doc.isEmpty())
        return;

    if (doc["type"].toString() == "DISPLAY_UPDATE")
        display_update_message(doc);
}