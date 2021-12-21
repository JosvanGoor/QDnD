#ifndef MODEL_PLAYER_H
#define MODEL_PLAYER_H

#include <QColor>
#include <QJsonArray>
#include <QJsonObject>
#include <QLine>
#include <QMap>
#include <QString>
#include <QVector>

#include "../opengl/staticmesh.h"
#include "../utility/enums.h"

struct DrawLine
{
    QColor color;
    QVector<QPoint> points;
};


class Player
{
    // core player values
    QString d_identifier;
    QColor d_color;

    // battlemat layer
    QPoint d_position;
    QString d_avatar_key;
    GridScale d_scale;

    // line layer
    QMap<QString, DrawLine> d_lines;
    StaticMesh<2, 3, 0> *d_lines_mesh;

    public:
        Player();
        Player(QString const &id, QString const &key, QColor const &col, GridScale size = GridScale::MEDIUM);
        ~Player();

        // getters
        QString const &identifier() const;
        QString const &avatar_key() const;
        QPoint const &position() const;
        QColor const &color() const;
        GridScale size() const;
        QMap<QString, DrawLine> const &lines() const;
        
        // setters
        void set_line_mesh(StaticMesh<2, 3, 0> *mesh);
        void set_position(QPoint const &pos);

        // lines
        void add_line(QString const &name, DrawLine const &line);
        void remove_line(QString const &name);
        void clear_lines();
        
        void render_lines();
        void regenerate_line_mesh();

        // serialize
        QJsonObject serialize() const noexcept;
        // QJsonArray serialize_lines() const noexcept;
};

#endif