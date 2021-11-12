#ifndef CONNECTIONEMITTER_H
#define CONNECTIONEMITTER_H

#include <QtCore>
#include <QString>

#include <iostream> //_DBG

class ConnectionEmitter : public QObject
{
    Q_OBJECT

    public:
        // ConnectionEmitter();
        // virtual ~ConnectionEmitter();

    signals:
        void connection_status_update(QString const &str);
};

#endif