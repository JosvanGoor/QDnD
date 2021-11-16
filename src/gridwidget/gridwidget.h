#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QBrush>
#include <QColor>
#include <QKeyEvent>
#include <QLine>
#include <QMap>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QVector>
#include <QWheelEvent>
#include <QWidget>

#include "../gridcontrolwidget/gridcontrolwidget.h"

#include <iostream> // _DBG

struct Line
{
    QVector<QLine> line;
    QColor color;
};

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

    QVector<QLine> d_current_line;
    QMap<QString, Line> d_line_cache;
    GridControlWidget *d_control;
    QMap<QString, AvatarControl> d_avatars;
    QString d_controlled_avatar;

    public:
        GridWidget(GridControlWidget *control, QWidget *parent = nullptr);

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
        void paint_line(QPainter *painter, QVector<QLine> const &lines, QColor color);
        void paint_current_line(QPainter *painter);
        void paint_line_cache(QPainter *painter);
        void paint_avatars(QPainter *painter);

        // avatar stuff
        void add_avatar(QString const &name, QPixmap const &avatar);
        void move_avatar(QString const &name, QPoint const &pos);
        void delete_avatar(QString const &name);
        QString const &controlled_avatar();
        void set_controlled_avatar(QString const &name);

        // input events
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        // void wheelEvent(QWheelEvent *event) override;
        // void keyReleaseEvent(QKeyEvent *event) override;

        void add_line(QString const &name, QColor const &color, QVector<QLine> const &line);
        void remove_line(QString const &name);
        void silent_remove_line(QString const &name);

    signals:
        void line_removed(QString const &name);
        void line_drawn(QVector<QLine> const &lines);
        void avatar_moved(QString const &name, QPoint const &pos);
};

#endif