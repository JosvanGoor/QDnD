#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QBrush>
#include <QColor>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QWheelEvent>
#include <QWidget>

#include <iostream> // _DBG

class GridWidget : public QWidget
{
    Q_OBJECT

    // grid stuff
    float d_scale;
    int d_gridsize;
    int d_offset_x;
    int d_offset_y;
    QColor d_foreground_color;
    QColor d_background_color;

    // events stuff
    QPoint d_mouse_old_position;
    bool d_right_mouse_button_down;
    bool d_left_mouse_button_down;

    public:
        GridWidget(QWidget *parent = nullptr);

        // setters / getters
        float scale() const noexcept;
        size_t gridsize() const noexcept;
        QColor const &foreground_color() const noexcept;
        QColor const &background_color() const noexcept;

        void set_scale(float scale) noexcept;
        void set_gridsize(size_t gridsize) noexcept;
        void set_foreground_color(QColor const &color) noexcept;
        void set_background_color(QColor const &color) noexcept;

        // painting
        void paintEvent(QPaintEvent *event) override;
        void paint_grid(QPainter *painter);

        // mouse events
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;
};

#endif