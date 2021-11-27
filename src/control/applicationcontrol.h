#ifndef CONTROL_APPLICATIONCONTROL_H
#define CONTROL_APPLICATIONCONTROL_H

#include <QObject>

/*
    Central control class

    Manages sub controllers, RuntimeCache and Network
*/

class ApplicationControl : public QObject
{
    Q_OBJECT

    public:
        explicit ApplicationControl(QObject *parent = nullptr);
        ~ApplicationControl();
};

#endif