#ifndef VIEW_STATUSBAR_H
#define VIEW_STATUSBAR_H

#include <QLabel>
#include <QStatusBar>

class StatusBar : public QStatusBar
{
    Q_OBJECT

    QLabel *d_connection_status;
    QLabel *d_data_connection_status;

    public:
        explicit StatusBar(QWidget *parent = nullptr);
        ~StatusBar();

    public slots:
        void update_connection_status(QString const &str);
        void update_data_connection_status(QString const &str);
        void status_message(QString const &str, int timeout_ms);
};

#endif