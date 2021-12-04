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

    QString d_own_identifier;
    QMap<QString, Player> d_players;

    public:
        explicit PlayerControl(QObject *parent = nullptr);
        ~PlayerControl();

        // utility
        QMap<QString, Player> &players();
        Player &player(QString const &identifier);

        // self
        QString const &own_identifier() const noexcept;
        void set_own_identifier(QString const &id) noexcept;

    public slots:
        void on_player_joins(QJsonObject const &doc);
        void on_player_leaves(QString const &name);

    signals:
        void debug_message(QString const &message);
        // server only
        void trigger_synchronization(QString const &identifier);

        void pixmap_required(QString const &key);
        void player_connected(Player const &player);
        void player_disconnected(QString const &name);
};

#endif