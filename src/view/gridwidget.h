#ifndef VIEW_GRIDWIDGET_H
#define VIEW_GRIDWIDGET_H

#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QWidget>

#include "../control/mapmanager.h"
#include "../control/playercontrol.h"
#include "../utility/enums.h"
#include "../utility/painting.h"


class GridWidget : public QWidget
{
    Q_OBJECT

    // drawing stuff
    float d_zoom;
    QPoint d_offset;
    QColor d_draw_color;

    // linedraw
    QPoint d_line_start;
    QPoint d_line_end;
    QVector<QLine> d_line_segments;

    // mouse
    QPoint d_mouse_old;
    QPoint d_worldmouse_old;
    MouseMode d_mouse_mode;
    bool d_snap_horizontal; // for grid items
    bool d_snap_vertical; // for grid items
    bool d_snap_offset_x; // for grid items
    bool d_snap_offset_y;
    bool d_left_button;
    bool d_right_button;

    // grid editing
    QPixmap d_gi_pixmap;
    int d_gi_rotation;
    GridScale d_gi_scale;

    public:
        explicit GridWidget(QWidget *parent = nullptr);
        ~GridWidget();

        // painting
        void paintEvent(QPaintEvent *event);

        // utility
        void set_draw_color(QColor color);
        void set_mouse_mode(MouseMode mode);
        void request_render_update();
        QPoint snap_to_grid(QPoint const &point, bool round = true);
        QPoint world_pos(QPoint const &point);
        QPoint grid_item_snap(QPoint const &point);
        void reset_offset();

        // gi stuff
        void set_snap_modes(bool horizontal, bool vertical, bool xoff, bool yoff);
        void update_gi_pixmap(QPixmap const &pixmap);
        void update_gi_rotation(int rotation);
        void update_gi_scale(GridScale scale);

        // mouse events
        void mouseMoveEvent(QMouseEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;

    signals:
        void debug_message(QString const &message);
        void grid_player_move(QPoint const &point);
        void grid_line_drawn(QVector<QLine> const &line, QColor const &color);

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