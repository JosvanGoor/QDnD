#include "clientconnection.h"

////////////////////
//  Constructors  //
////////////////////

ClientConnection::ClientConnection(QObject *parent)
:   ConnectionBase(parent)
{
    d_socket_state.socket = new QTcpSocket;

    QObject::connect(d_socket_state.socket, &QTcpSocket::connected, this, &ClientConnection::on_connected);
    QObject::connect(d_socket_state.socket, &QTcpSocket::errorOccurred, this, &ClientConnection::on_socket_error);
    QObject::connect(d_socket_state.socket, &QTcpSocket::readyRead, this, &ClientConnection::on_socket_readyread);
}


ClientConnection::~ClientConnection()
{
    delete d_socket_state.socket;
}


////////////////////
//     Public     //
////////////////////

void ClientConnection::connect(QString const &host, uint16_t port)
{
    d_socket_state.socket->connectToHost(host, port);
}


void ClientConnection::disconnect()
{
    d_socket_state.socket->close();
    connection_status_update("No Connection");
}


bool ClientConnection::is_connected()
{
    return d_socket_state.socket->state() == QTcpSocket::ConnectedState;
}


bool ClientConnection::is_server()
{
    return false;
}


void ClientConnection::send(QJsonDocument const &doc, [[maybe_unused]] bool signal_self)
{
    send_json_blob(d_socket_state.socket, doc);
    // if (signal_self)
    //     signal_message(doc, d_socket_state);
}

////////////////////
//     Slots      //
////////////////////

void ClientConnection::on_connected()
{
    debug_message("ClientConnection successfully established.");
    connection_status_update("Connected to " + d_socket_state.socket->peerAddress().toString());
}


void ClientConnection::on_socket_error(QAbstractSocket::SocketError error)
{
    QString errstr = QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error);
    debug_message("Connection: " + errstr);
    disconnect();
}


void ClientConnection::on_socket_readyread()
{
    QJsonDocument doc = read_connection(d_socket_state);
    
    while (!doc.isEmpty()) // maybe we received more then 1 message.
    {
        signal_message(doc, d_socket_state);
        doc = read_connection(d_socket_state);
    }
}
