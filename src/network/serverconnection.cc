#include "serverconnection.h"

////////////////////
//  Constructors  //
////////////////////

ServerConnection::ServerConnection(QObject *parent)
:   ConnectionBase(parent)
{
    d_server = new QTcpServer;

    QObject::connect(d_server, &QTcpServer::newConnection, this, &ServerConnection::on_new_connection);
    QObject::connect(&d_ping_timer, &QTimer::timeout, this, &ServerConnection::on_ping_timer);
}


ServerConnection::~ServerConnection()
{
    disconnect();
    delete d_server;
}


////////////////////
//     Public     //
////////////////////

void ServerConnection::start_listening(uint16_t port)
{
    if (!d_server->listen(QHostAddress::Any, port))
        connection_status_update("Failed to start listening to port " + QString::number(port));
    
    d_ping_timer.setInterval(45'000);
    d_ping_timer.start(45'000);
}


void ServerConnection::disconnect()
{
    for (auto it = d_connections.begin(); it != d_connections.end(); ++it)
    {
        it.value().socket->close();
        delete it.key();
    }

    d_server->close();
    d_connections.clear();
    d_ping_timer.stop();
}


bool ServerConnection::is_connected()
{
    return d_server->isListening();
}


bool ServerConnection::is_server()
{
    return true;
}


void ServerConnection::send(QJsonDocument const &doc)
{
    QByteArray blob = doc.toJson();

    for (auto it = d_connections.begin(); it != d_connections.end(); ++it)
        send_blob(it.value().socket, blob);
}


////////////////////
//     Slots      //
////////////////////

void ServerConnection::on_ping_timer()
{
    send(ping_message());
}


void ServerConnection::on_new_connection()
{
    QTcpSocket *socket;
    while ((socket = d_server->nextPendingConnection()) != nullptr)
    {
        emit debug_message("New Connection!");
        
        // TODO: request server state for new client
        d_connections[socket] = {socket, {}, 0, ""};
        QObject::connect(socket, &QTcpSocket::errorOccurred, this, &ServerConnection::on_socket_error);
        QObject::connect(socket, &QTcpSocket::readyRead, this, &ServerConnection::on_socket_readyread);
        QObject::connect(socket, &QTcpSocket::disconnected, this, &ServerConnection::on_socket_disconnected);
    }
}


void ServerConnection::on_socket_error(QAbstractSocket::SocketError error)
{
    QObject *id = QObject::sender();
    SocketState &state = d_connections.find(id).value();
    QString name = state.identifier.isEmpty() ? "[[Unknown]]" : state.identifier;
    debug_message("SocketError " + QString::number(error) + " from " + name);
}


void ServerConnection::on_socket_readyread()
{
    QObject *id = QObject::sender();
    SocketState &state = d_connections.find(id).value();
    QJsonDocument doc = read_connection(state);

    if (doc.isEmpty())
        return; 

    // TODO: handle message
    debug_message("Received json doc: " + QString(doc.toJson()));
}


void ServerConnection::on_socket_disconnected()
{
    QObject *id = QObject::sender();
    // TODO: notify app control
    d_connections.remove(id);
    delete id;
}