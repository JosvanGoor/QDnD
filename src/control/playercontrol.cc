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
//     Slots      //
////////////////////

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

    debug_message("Player joined with scale " + as_string(scale));

    emit pixmap_required(avatar_key);
    emit player_connected(d_players[id]);
    emit trigger_synchronization(id);
}


void PlayerControl::on_player_leaves(QString const &name)
{
    d_players.remove(name);
    emit player_disconnected(name);
}