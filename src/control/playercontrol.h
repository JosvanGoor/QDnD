#ifndef CONTROL_PLAYERCONTROL_H
#define CONTROL_PLAYERCONTROL_H

#include <QColor>
#include <QMap>
#include <QObject>

#include "../model/player.h"
#include "../utility/enums.h"

/*
    Manages players info, has a few signals that are connected for servers only
*/

class PlayerControl : public QObject
{
    Q_OBJECT

    uint64_t d_unique_number;
    QString d_own_identifier;
    QMap<QString, Player> d_players;

    public:
        explicit PlayerControl(QObject *parent = nullptr);
        ~PlayerControl();

        // utility
        QMap<QString, Player> &players();
        Player &player(QString const &identifier);
        void clear();

        // self
        void create_dungeon_master(QString const &avatar_key);
        Player &own_player();
        QString unique_name();
        QString const &own_identifier() const noexcept;
        void set_own_identifier(QString const &id) noexcept;

    public slots:
        void on_player_joins(QJsonObject const &doc);
        void on_player_leaves(QString const &name);
        void on_player_moves(QString const &id, QPoint const &newpos);

        void on_line_received(QJsonObject const &doc);
        void on_lines_removed(QJsonObject const &obj);
        void on_lines_cleared(QString const &id);

    signals:
        void update_grid();
        void debug_message(QString const &message);
        // server only
        void trigger_synchronization(QString const &identifier);

        void pixmap_required(QString const &key);
        void player_connected(Player const &player);
        void player_disconnected(QString const &name);
};

#endif