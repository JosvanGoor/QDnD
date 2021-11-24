#ifndef GRID_GRID_H
#define GRID_GRID_H

#include <QColor>
#include <QString>

#include "griditemgroup.h"
#include "../utility/enums.h"




class GridModel
{
    GridItemGroup d_items;
    QColor d_foreground_color;
    QColor d_background_color;

    public:
        GridModel();
        ~GridModel();

        // setters
        void set_foreground_color(QColor const &color);
        void set_background_color(QColor const &color);

        // getters
        GridItemGroup &items() noexcept;
        QColor foreground_color() const noexcept;
        QColor background_color() const noexcept;

};

#endif