#ifndef APPLICATIONCONTROL_H
#define APPLICATIONCONTROL_H

#include <QApplication>
#include <QMap>
#include <QObject>

#include "../model/runtimemodel.h"
#include "../view/mainwindow.h"
#include "../network/connectionbase.h"

class ApplicationControl : public QObject
{
    Q_OBJECT

    ConnectionBase *d_connection;
    MainWindow *d_main_window;
    RuntimeModel *d_runtime_model;
    QMap<QString, QString> d_settings;

    public:
        explicit ApplicationControl(QObject *parent = nullptr);
        ~ApplicationControl();

    private:
        void load_settings() noexcept;

        // Chatwidget stuff
        void chatwidget_setup();
        void on_chatwidget_message_entered(QString const &msg);
        
        // mainwindow stuff
        void mainwindow_setup();

        // menubar stuff
        void menubar_setup();
        void on_menubar_quit();
        void on_menubar_host();
        void on_menubar_connect();
        void on_menubar_disconnect();

        // spellswidget stuff
        void spellswidget_setup();
        void on_spellswidget_selection_change(QString const &name);

        // statusbar stuff
        void statusbar_setup();

    signals:
        void debug_output(QString const &message);
        void chatmessage_info(QString const &message);
        void connection_info(QString const &message);
        void statusbar_message(QString const &message, int timeout = 10000);
};

#endif