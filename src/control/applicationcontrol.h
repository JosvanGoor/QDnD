#ifndef APPLICATIONCONTROL_H
#define APPLICATIONCONTROL_H

#include <QApplication>
#include <QMap>
#include <QMessageBox>
#include <QObject>

#include "../model/runtimemodel.h"
#include "../view/connectdialog.h"
#include "../view/mainwindow.h"
#include "../network/clientconnection.h"
#include "../network/messagebuilding.h"
#include "../network/connectionbase.h"
#include "../network/serverconnection.h"

class ApplicationControl : public QObject
{
    Q_OBJECT

    ConnectionBase *d_connection;
    MainWindow *d_main_window;
    RuntimeModel *d_runtime_model;
    QMap<QString, QString> d_settings;

    QString d_identifier; // own name

    public:
        explicit ApplicationControl(QObject *parent = nullptr);
        ~ApplicationControl();

    private:
        void load_settings() noexcept;

        // Chatwidget stuff
        void chatwidget_setup();
        void on_chatwidget_message_entered(QString const &msg);
        void on_chatwidget_user_message(QString const &name, QString const &message);
        
        // networking  stuff
        bool reconnect_confirmation();
        void connection_setup();
        void player_connected(QString const &name, QByteArray const &b64_avatar, QColor const &color);
        void player_disconnected(QString const &name);

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