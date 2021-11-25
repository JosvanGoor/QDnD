#ifndef GRID_GRID_H
#define GRID_GRID_H

#include <QColor>
#include <QMap>
#include <QPoint>
#include <QString>
#include <QVector>

#include "griditemgroup.h"
#include "../utility/enums.h"

struct GridLine
{
    QColor color;
    QVector<QPoint> points;
};


class GridModel
{
    QString d_name;
    QColor d_foreground_color;
    QColor d_background_color;
    QMap<QString, GridItemGroup> d_items;
    QMap<QString, QMap<QString, GridLine>> d_lines;

    public:
        GridModel();
        ~GridModel();

        // setters
        void set_name(QString const &name);
        void set_foreground_color(QColor const &color);
        void set_background_color(QColor const &color);

        // getters
        QString const &name() const noexcept;
        QColor foreground_color() const noexcept;
        QColor background_color() const noexcept;
        GridItemGroup &items(QString const &name) noexcept;

        // manipulation
        void add_line(QString const &user, QString const &name, GridLine const &line);
        void remove_line(QString const &user, QString const &line);
        void remove_user_lines(QString const &user);
};

#endif