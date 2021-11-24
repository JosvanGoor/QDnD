#ifndef VIEW_GRIDWIDGET_H
#define VIEW_GRIDWIDGET_H

#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QWidget>

#include "../model/gridmodel.h"

class GridWidget : public QWidget
{
    Q_OBJECT

    // grid drawing stuff
    int d_gridsize;
    QPoint d_offset;

    // mouse
    QPoint d_mouse_old;

    // to render
    GridModel *d_grid_model;

    public:
        explicit GridWidget(QWidget *parent = nullptr);
        ~GridWidget();

        // painting
        void paintEvent(QPaintEvent *event);
        void paint_grid(QPainter &painter);
};

#endif