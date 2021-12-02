#ifndef CONTROL_APPLICATIONCONTROL_H
#define CONTROL_APPLICATIONCONTROL_H

#include <QFileDialog>
#include <QMessageBox>
#include <QObject>

#include "playercontrol.h"
#include "../expressions/diceparser.h"
#include "../model/pixmapcache.h"
#include "../model/spell.h"
#include "../network/clientconnection.h"
#include "../network/connectionbase.h"
#include "../network/serverconnection.h"
#include "../view/connectdialog.h"
#include "../view/mainwindow.h"

/*
    Central control class

    Manages sub controllers, RuntimeCache and Network
*/

class ApplicationControl : public QObject
{
    Q_OBJECT

    PixmapCache d_pixmap_cache;
    QMap<QString, Spell> d_spells;
    PlayerControl d_player_control;
    MainWindow d_main_window;

    ConnectionBase *d_connection;


    public:
        explicit ApplicationControl(QObject *parent = nullptr);
        ~ApplicationControl();

        // initialisation
        void create_default_connections();
        void load_spells(QString const &filename);

    public slots:
        // networking
        bool verify_close_connection();
        void start_hosting();
        void connect_to_host();
        void set_connectionbase_signals();

        // general slots
        void on_pixmap_required(QString const &key);
        void on_player_connected(Player const &player);
        void on_player_disconnected(QString const &id);
        void on_spell_selection(QString const &name);
        void on_display_update(QString const &key);

        // chat
        void chat_entered(QString const &chat);

        // menu's
        void display_update_clicked();
        
        // server only slots
        void pixmap_requested(QString const &id, QString const &key);
        void on_trigger_synchronization(QString const &identifier);

    signals:
        void debug_message(QString const &key);

};

#endif