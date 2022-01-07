#ifndef NETWORK_DATACONNECTIONBASE_H
#define NETWORK_DATACONNECTIONBASE_H

#include <QByteArray>
#include <QJsonDocument>
#include <QMetaEnum>
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
        virtual void queue(QJsonDocument const &doc) = 0;
        virtual void connect(QString const &id, QString const &host, uint16_t port = 41201) = 0;
        virtual void disconnect() = 0;

    protected:
        void write_blob(QTcpSocket *socket, QByteArray const &data, bool limited);
        void write_json(QTcpSocket *socket, QJsonDocument const &doc, bool limited = true);
        QJsonDocument read(QTcpSocket *socket, int &incoming, QByteArray &buffer);

    signals:
        void debug_message(QString const &message);
        void connection_status(QString const &message);

        void message_received(QJsonDocument const &doc);
};

#endif