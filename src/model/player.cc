#include "player.h"

////////////////////
//  Constructors  //
////////////////////

Player::Player()
{ }


Player::Player(QString const &id, QString const &key, QColor const &col, GridScale size)
:   d_identifier(id),
    d_color(col),
    d_position(0, 0),
    d_avatar_key(key),
    d_scale(size),
    d_lines(),
    d_lines_mesh(nullptr)
{ }


Player::~Player()
{
    if (d_lines_mesh)
        delete d_lines_mesh;
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
    return d_scale;
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


void Player::set_line_mesh(StaticMesh<2, 3, 0> *mesh)
{
    d_lines_mesh = mesh;
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


void Player::render_lines()
{
    d_lines_mesh->render(GL_LINES);
}


void Player::regenerate_line_mesh()
{
    QVector<float> mesh;

    for (auto &line : d_lines)
    {
        if (line.points.isEmpty())
            continue;
        float r = line.color.redF();
        float g = line.color.greenF();
        float b = line.color.blueF();
        for (int idx = 0; idx < (line.points.size() - 1); ++idx)
        {
            mesh +=
            {
                float(line.points[idx].x()), float(line.points[idx].y()),           r, g, b,
                float(line.points[idx + 1].x()), float(line.points[idx + 1].y()),   r, g, b,
            };
        }
    }

    d_lines_mesh->update(mesh);
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
    obj["scale"] = as_int(d_scale);
    obj["x"] = d_position.x();
    obj["y"] = d_position.y();
    return obj;
}