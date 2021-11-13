#include "connectioncommon.h"

QJsonDocument ConnectionCommon::read_socket(QTcpSocket *sock, uint32_t &incoming, QByteArray &buffer)
{
    QByteArray data = sock->readAll();
    buffer.append(data);

    if (incoming == 0 && buffer.size() < 4)
        return {};

    if (incoming == 0) // begin packet
    {
        // we read 4 bytes, which indicate the size of the following message
        incoming = *reinterpret_cast<uint32_t*>(buffer.data());
        buffer.remove(0, 4);
        emit debug_message("Incoming: " + QString::number(incoming) + " bytes.");
    }

    if (buffer.size() >= incoming)
    {
        QJsonDocument document = QJsonDocument::fromJson(buffer.left(incoming));
        buffer.remove(0, incoming);
        incoming = 0;

        return document;
    }

    // read + parse payload.
    return {};
}
