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
#include "../utility/painting.h"
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

        // grid control
        void on_grid_line_drawn(QVector<QLine> const &lines, QColor const &color);
        void on_grid_player_move(QPoint const &point);

        // misc
        void chat_entered(QString const &chat);
        void display_update_clicked();
        
        // server only slots
        void pixmap_requested(QString const &id, QString const &key);
        void on_trigger_synchronization(QString const &identifier);

        // painting stuff
        void on_paint_ground_layer(QPainter &painter, QSize size, QPoint offset, QPoint mousepos);
        void on_paint_player_layer(QPainter &painter, QSize size, QPoint offset, QPoint mousepos);
        void on_paint_entity_layer(QPainter &painter, QSize size, QPoint offset, QPoint mousepos);
        void on_paint_mouse_layer(QPainter &painter, QSize size, QPoint offset, QPoint mousepos);

    signals:
        void update_grid();
        void debug_message(QString const &key);

};

#endif