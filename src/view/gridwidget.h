#ifndef VIEW_GRIDWIDGET_H
#define VIEW_GRIDWIDGET_H

#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QWidget>

#include "../control/playercontrol.h"
#include "../model/gridmodel.h"
#include "../utility/painting.h"

class GridWidget : public QWidget
{
    Q_OBJECT

    // grid drawing stuff
    int d_gridsize;
    QPoint d_offset;

    // mouse
    QPoint d_mouse_old;

    public:
        explicit GridWidget(QWidget *parent = nullptr);
        ~GridWidget();

        // painting
        void paintEvent(QPaintEvent *event);

    signals:
        // paints grid, background color & brushes (TODO)
        // then  paints scenery
        void paint_ground_layer(QPainter &painter, QSize size, QPoint offset, QPoint mousepos);
        // paints lines etc drawn by players
        void paint_player_layer(QPainter &painter, QSize size, QPoint offset, QPoint mousepos);
        // paints entities (players & monsters)
        void paint_entity_layer(QPainter &painter, QSize size, QPoint offset, QPoint mousepos);
        // paints mouse related things (pings & aoe markers)
        void paint_mouse_layer(QPainter &painter, QSize size, QPoint offset, QPoint mousepos);
};

#endif