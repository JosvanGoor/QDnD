#include "clientconnection.h"

////////////////////
//  Constructors  //
////////////////////

ClientConnection::ClientConnection(QObject *parent)
:   ConnectionBase(parent)
{
    d_socket = new QTcpSocket;
}


ClientConnection::~ClientConnection()
{
    delete d_socket;
}


////////////////////
//     Public     //
////////////////////

void ClientConnection::connect(QString const &host, uint16_t port)
{
    d_socket->connectToHost(host, port);
}


void ClientConnection::disconnect()
{
    d_socket->close();
}


bool ClientConnection::is_connected()
{
    return d_socket->state() == QTcpSocket::ConnectedState;
}


bool ClientConnection::is_server()
{
    return false;
}


void ClientConnection::send(QJsonDocument const &doc)
{
    send_json_blob(d_socket, doc);
}

////////////////////
//     Slots      //
////////////////////

void ClientConnection::on_connected()
{
    // update connection info
    // send user info to server
}


void ClientConnection::on_socket_error(QAbstractSocket::SocketError error)
{
    // update connection info
    // report error
}


void ClientConnection::on_socket_readyread()
{
    QJsonDocument doc = read_connection(d_socket, d_socket_state);
    
    while (!doc.isEmpty()) // maybe we received more then 1 message.
    {
        // parse document

        doc = read_connection(d_socket, d_socket_state);
    }
}