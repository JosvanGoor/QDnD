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

// will be replaced with a more complex version soon(tm)
struct Entity
{
    QString avatar_key;
    QPoint position;
    GridScale scale;
};

/*
    Central control class

    Manages sub controllers, RuntimeCache and Network
*/

class ApplicationControl : public QObject
{
    Q_OBJECT

    PixmapCache d_pixmap_cache;
    PlayerControl d_player_control;
    MainWindow d_main_window;

    QSet<QString> d_line_selection;
    QSet<QString> d_entity_selection;

    QMap<QString, Spell> d_spells;
    QMap<QString, Entity> d_entities;

    ConnectionBase *d_connection;

    public:
        explicit ApplicationControl(QObject *parent = nullptr);
        ~ApplicationControl();

        // initialisation
        void create_default_connections();
        void load_spells(QString const &filename);

        void reset();

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
        void on_line_sync(QJsonObject const &obj);
        void on_pixmap_received(QString const &key, QPixmap const &pixmap);

        // grid control
        void on_grid_line_drawn(QVector<QLine> const &lines, QColor const &color);
        void on_grid_player_move(QPoint const &point);
        void on_grid_delete_lines(QVector<QString> const &lines);
        void on_grid_line_selection(QSet<QString> const &lines);
        void on_grid_delete_all_lines();

        // host entity control
        void on_host_entity_added(QString const &name, QString const &filename);
        void on_host_entities_removed(QVector<QString> const &entities);
        void on_host_entities_cleared();
        void on_host_entities_selection(QSet<QString> const &names);

        // client entity control
        void on_entity_added(QJsonObject const &obj);
        void on_entities_removed(QJsonObject const &obj);
        void on_entities_cleared();
        void on_entities_moved(QJsonObject const &obj);
        void on_synchronize_entities(QJsonObject const &obj);

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