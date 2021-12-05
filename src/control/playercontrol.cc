#include "playercontrol.h"

////////////////////
//  Constructor   //
////////////////////

PlayerControl::PlayerControl(QObject *parent)
:   QObject(parent)
{

}


PlayerControl::~PlayerControl()
{
    
}


////////////////////
//    Utility     //
////////////////////

QMap<QString, Player> &PlayerControl::players()
{
    return d_players;
}


Player &PlayerControl::player(QString const &identifier)
{
    static Player placeholder{"", "", Qt::black, GridScale::GARGANTUAN};

    if (auto it = d_players.find(identifier); it != d_players.end())
        return it.value();

    return placeholder;
}


////////////////////
//      Self      //
////////////////////

void PlayerControl::create_dungeon_master(QString const &avatar_key)
{
    Player player{"Dungeon Master", avatar_key, Qt::black};
    d_players[player.identifier()] = player;
    d_own_identifier = player.identifier();
    emit player_connected(player);
}


QString PlayerControl::unique_name()
{
    return d_own_identifier + " " + QString::number(d_unique_number++);
}


QString const &PlayerControl::own_identifier() const noexcept
{
    return d_own_identifier;
}


void PlayerControl::set_own_identifier(QString const &id) noexcept
{
    d_own_identifier = id;
}


////////////////////
//     Slots      //
////////////////////

void PlayerControl::on_player_joins(QJsonObject const &doc)
{
    QString id = doc["id"].toString();
    QString avatar_key = doc["avatar"].toString();
    QColor color = doc["color"].toString().toUInt();
    GridScale scale = static_cast<GridScale>(doc["scale"].toInt());
    
    d_players[id] = {id, avatar_key, color, scale};
    d_players[id].set_position({doc["x"].toInt(), doc["y"].toInt()});

    emit pixmap_required(avatar_key);
    emit player_connected(d_players[id]);
    emit trigger_synchronization(id);
}


void PlayerControl::on_player_leaves(QString const &name)
{
    d_players.remove(name);
    emit player_disconnected(name);
}


void PlayerControl::on_player_moves(QString const &id, QPoint const &newpos)
{
    d_players.find(id).value().set_position(newpos);
    update_grid();
}


void PlayerControl::on_line_received(QJsonObject const &doc)
{
    Player &artist = d_players.find(doc["id"].toString()).value();
    QJsonArray points = doc["points"].toArray();

    
    QVector<QLine> lines;
    for (int idx = 0; idx < (points.size() - 1); ++idx)
    {
        QPoint p1 = {points[idx].toObject()["x"].toInt(), points[idx].toObject()["y"].toInt()};
        QPoint p2 = {points[idx + 1].toObject()["x"].toInt(), points[idx + 1].toObject()["y"].toInt()};
        lines.push_back({p1, p2});
    }

    QString name = doc["name"].toString();
    QColor color = static_cast<unsigned int>(doc["color"].toInt());
    artist.add_line(name, {color, lines});
    update_grid();
}