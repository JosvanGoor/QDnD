#include "hostconnection.h"

void HostConnection::on_incoming_data()
{
    QObject *sender = QObject::sender();
    emit debug_message("Sender ptr: " + QString::number((((uintptr_t)sender))) + "\n");
    std::cout << "Sender: " << static_cast<void*>(sender) << "\n" << std::flush;

    if (auto it = d_clients.find(sender); it != d_clients.end())
    {
        ConnectionState &conn = it.value();
        QJsonDocument document = read_socket(conn.d_socket, conn.incoming_size, conn.d_buffer);
        if (document.isEmpty())
            return;

        emit debug_message("Name of connection is: " + document["character_name"].toString());
    }
    else
        emit debug_message("Connection not found frowny face");
}