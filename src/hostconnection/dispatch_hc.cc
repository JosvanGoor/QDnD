#include "hostconnection.h"

void HostConnection::dispatch(QJsonDocument const &doc)
{
    QString blob = doc.toJson();
    QByteArray binary = blob.toLocal8Bit();
    
    for (auto it : d_clients)
    {
        std::cout << "Sending blob!\n" << std::flush;
        send_blob(it.d_socket, binary);
    }
}