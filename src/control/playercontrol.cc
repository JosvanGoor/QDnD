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

void PlayerControl::on_player_joins(QJsonObject const &doc)
{
    // TODO: implement
}


void PlayerControl::on_player_leaves(QString const &name)
{
    // TODO: implement
}