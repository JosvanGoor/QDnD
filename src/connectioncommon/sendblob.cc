#include "connectioncommon.h"

void ConnectionCommon::send_blob(QTcpSocket *socket, QByteArray const &data)
{
    uint32_t size = data.size();

    socket->write(reinterpret_cast<char*>(&size), 4);
    socket->write(data);
}