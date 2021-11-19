#include "networking.h"

#include <iostream>

void send_blob(QTcpSocket *socket, QByteArray const &blob, bool limited)
{
    uint32_t size = blob.size();
    if (limited && blob.size() > 1'000'000) // we send nothing over 1MB
    {
        std::cerr << "Blob larger then 500'000bytes not sent.\n" << std::flush;
        return;
    }

    socket->write(reinterpret_cast<char*>(&size), 4);
    socket->write(blob);
}


void send_json_blob(QTcpSocket *socket, QJsonDocument const &document, bool limited)
{
    QByteArray data = document.toJson();
    send_blob(socket, data, limited);
}


QJsonDocument read_connection(QTcpSocket *socket, SocketState &state)
{
    QJsonDocument document;
    state.buffer.append(socket->readAll());

    // for some reason we received less then 1 int.
    if (state.incoming == 0 && state.buffer.size() < 4)
        return document;

    // start of a new packet
    if (state.incoming == 0)
    {
        state.incoming = *reinterpret_cast<uint32_t*>(state.buffer.data());
        state.buffer.remove(0, 4);
    }

    // payload complete, parse and return
    if (state.buffer.size() >= state.incoming)
    {
        document = QJsonDocument::fromJson(state.buffer.left(state.incoming));
        state.buffer.remove(0, state.incoming);
        state.incoming = 0;

        return document;
    }

    // payload incomplete
    return document;
}
