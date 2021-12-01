#include "player.h"

////////////////////
//  Constructors  //
////////////////////

Player::Player(QString const &id, QString const &key, QColor const &col, GridScale size)
:   d_identifier(id),
    d_avatar_key(key),
    d_color(col),
    d_size(size)
{

}


Player::~Player()
{

}


////////////////////
//    Getters     //
////////////////////

QString const &Player::identifier() const
{
    return d_identifier;
}


QString const &Player::avatar_key() const
{
    return d_avatar_key;
}


QColor const &Player::color() const
{
    return d_color;
}


GridScale Player::size() const
{
    return d_size;
}


////////////////////
//   Serialize    //
////////////////////

QJsonObject Player::serialize() const noexcept
{
    QJsonObject obj;
    obj["identifier"] = d_identifier;
    obj["avatar_key"] = d_avatar_key;
    obj["color"] = QString::number(d_color.rgb(), 16);
    obj["size"] = as_int(d_size);
    return obj;
}