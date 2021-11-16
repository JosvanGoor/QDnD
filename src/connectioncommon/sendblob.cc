#include "connectioncommon.h"

void ConnectionCommon::send_blob(QTcpSocket *socket, QByteArray const &data)
{
    uint32_t size = data.size();
    if (data.size() > 500'000)
    {
        debug_message("Stop trying to break me =(");
        return;
    }

    socket->write(reinterpret_cast<char*>(&size), 4);
    socket->write(data);
}