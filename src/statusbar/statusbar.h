#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include <QStatusBar>

class StatusBar : public QStatusBar
{
    Q_OBJECT
    
    QLabel *d_connection_status;

    public:
        explicit StatusBar(QWidget *parent = nullptr);
        ~StatusBar();
};

#endif