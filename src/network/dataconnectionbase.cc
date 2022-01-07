#include "dataconnectionbase.h"

////////////////////
//  Constructor   //
////////////////////

DataConnectionBase::DataConnectionBase(QObject *parent)
:   QThread(parent)
{ }


DataConnectionBase::~DataConnectionBase()
{ }


////////////////////
//    Base IO     //
////////////////////

void DataConnectionBase::write_blob(QTcpSocket *socket, QByteArray const &data, bool limited)
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


void DataConnectionBase::write_json(QTcpSocket *socket, QJsonDocument const &doc, bool limited)
{
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    write_blob(socket, data, limited);
}


QJsonDocument DataConnectionBase::read(QTcpSocket *socket, int &incoming, QByteArray &buffer)
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