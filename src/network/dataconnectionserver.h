#ifndef NETWORK_DATACONNECTIONSERVER_H
#define NETWORK_DATACONNECTIONSERVER_H

#include <QMap>
#include <QTcpServer>
#include <QTimer>

#include "dataconnectionbase.h"
#include "socketstate.h"
#include "messagebuilder.h"

class DataConnectionServer : public DataConnectionBase
{
    uint16_t d_port;
    QTimer d_ping_timer;
    QTcpServer *d_server;
    QMap<QObject*, DataSocketState> d_connections;

    public:
        explicit DataConnectionServer(uint16_t port, QObject *parent = nullptr);
        ~DataConnectionServer();

        // thread main
        void run() override;
        
        // virtuals
        bool is_server() const noexcept;
        // void queue(QByteArray const &data);
        void queue(QJsonDocument const &doc);
        void connect(QString const &id, QString const &host, uint16_t port = 41201);
        void disconnect();

        // utility
        void update_status();
        void activate(DataSocketState &state);
        DataSocketState *state_by_identifier(QString const &id);
        void handle_message(QJsonDocument const &document, DataSocketState &state);

    public slots:
        void send_data_message(QString const &id, QJsonDocument const &doc);
        // void queue_message(QString const &id, QByteArray const &data);

    private slots:
        void on_ping_timer();
        void on_new_connection();
        void on_socket_error(QAbstractSocket::SocketError error);
        void on_socket_readyread();
        void on_socket_readywrite(uint16_t written);
        void on_socket_disconnect();


};

#endif