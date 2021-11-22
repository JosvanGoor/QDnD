#ifndef GRID_GRIDWIDGET_H
#define GRID_GRIDWIDGET_H

#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

#include "gridmousestate.h"

class GridWidget : public QWidget
{
    Q_OBJECT

    static constexpr int gridsize = 64;
    
    // window offsets
    int d_offset_x;
    int d_offset_y;

    // mouse stuff
    bool d_mouse_left_button_down;
    bool d_mouse_right_button_down;
    GridMouseState d_mouse_state;

    public:
        explicit GridWidget(QWidget *parent = nullptr);
        ~GridWidget();

        // painting
        void paintEvent(QPaintEvent *event) override;
        void paint_grid(QPainter &painter);
        void paint_mouse_pixmap(QPainter &painter);

        // input
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        
        GridMouseState &mouse_state();
};

#endif