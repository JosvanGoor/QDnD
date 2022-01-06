#ifndef NETWORK_DATACONNECTIONBASE_H
#define NETWORK_DATACONNECTIONBASE_H

#include <QByteArray>
#include <QJsonDocument>
#include <QString>
#include <QTcpSocket>
#include <QThread>

class DataConnectionBase : public QThread
{
    Q_OBJECT

    public:
        explicit DataConnectionBase(QObject *parent = nullptr);
        ~DataConnectionBase();

        virtual bool is_server() const noexcept = 0;

        virtual void queue(QByteArray const &data) = 0;
        virtual void queue(QJsonDocument const &doc) = 0;
        virtual void connect(QString const &str, uint16_t port = 41201) = 0;
        virtual void disconnect() = 0;

    protected:
        void write_blob(QTcpSocket *socket, QByteArray const &data, bool limited = false);
        void write_json(QTcpSocket *socket, QJsonDocument const &doc, bool limited = false);

    signals:
        void debug_message(QString const &message);
        void connection_status(QString const &message);

        void message_received(QJsonDocument const &doc);
};

#endif