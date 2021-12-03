#include "player.h"

////////////////////
//  Constructors  //
////////////////////

Player::Player()
{ }


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


QPoint const &Player::position() const
{
    return d_position;
};


QColor const &Player::color() const
{
    return d_color;
}


GridScale Player::size() const
{
    return d_size;
}


QMap<QString, DrawLine> const &Player::lines() const
{
    return d_lines;
}


////////////////////
//     Lines      //
////////////////////

void Player::set_position(QPoint const &pos)
{
    d_position = pos;
}


////////////////////
//     Lines      //
////////////////////

void Player::add_line(QString const &name, DrawLine const &line)
{
    d_lines[name] = line;
}


void Player::remove_line(QString const &line)
{
    if (auto it = d_lines.find(line); it != d_lines.end())
        d_lines.erase(it);
}


void Player::clear_lines()
{
    d_lines = QMap<QString, DrawLine>{};
}


////////////////////
//   Serialize    //
////////////////////

QJsonObject Player::serialize() const noexcept
{
    QJsonObject obj;
    obj["id"] = d_identifier;
    obj["avatar"] = d_avatar_key;
    obj["color"] = QString::number(d_color.rgb(), 16);
    obj["size"] = as_int(d_size);
    return obj;
}


QJsonArray Player::serialize_lines() const noexcept
{
    QJsonArray arr;

    for (auto it = d_lines.begin(); it != d_lines.end(); ++it)
    {
        QJsonArray points;
        for (size_t idx = 0; idx < it.value().line.size(); ++idx)
        {
            QJsonObject point;
            point["x"] = it.value().line[idx].x1();
            point["y"] = it.value().line[idx].y1();
            points.push_back(points);
        }

        // we take only start points of individual lines, since they match the
        // previous bit's end point. But of course then we need to take
        // the end for the last one or we are 1 short!
        if (!it.value().line.isEmpty())
        {
            QJsonObject point;
            point["x"] = it.value().line.back().x2();
            point["y"] = it.value().line.back().y2();
            points.push_back(points);
        }

        QJsonObject obj;
        obj["name"] = it.key();
        obj["color"] = QString::number(it.value().color.rgb(), 16);
        obj["points"] = points;
        arr.push_back(obj);
    }
}