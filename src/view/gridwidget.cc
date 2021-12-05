#include "gridwidget.h"

////////////////////
//  Constructors  //
////////////////////

GridWidget::GridWidget(QWidget *parent)
:   QWidget(parent)
{
    d_offset = {};
    d_draw_color = Qt::black;
    d_line_start = {};
    d_worldmouse_old = {};
    d_mouse_old = {};
    d_mouse_mode = MouseMode::MOVE_CHARACTER;
    d_left_button = false;
    d_right_button = false;

    setMouseTracking(true);
}


GridWidget::~GridWidget()
{
    
}


////////////////////
//    Painting    //
////////////////////

void GridWidget::paintEvent([[maybe_unused]] QPaintEvent *event)
{
    QPainter painter{this};

    painter.fillRect(0, 0, width(), height(), QBrush{Qt::white});
    
    emit paint_ground_layer(painter, size(), d_offset, d_mouse_old);
    emit paint_player_layer(painter, size(), d_offset, d_mouse_old);
    emit paint_entity_layer(painter, size(), d_offset, d_mouse_old);
    emit paint_mouse_layer(painter, size(), d_offset, d_mouse_old);

    // Paint currently happening things
    if (d_left_button)
    {
        switch (d_mouse_mode)
        {
            case MouseMode::LINE_DRAW:
                paint_line(painter, {{d_line_start, d_line_end}}, d_draw_color, d_offset);
            break;

            case MouseMode::FREE_DRAW:
                paint_line(painter, d_line_segments, d_draw_color, d_offset);
            break;

            default: break;
        }
    }
}


////////////////////
//    Utility     //
////////////////////

void GridWidget::set_draw_color(QColor color)
{
    d_draw_color = color;
}


void GridWidget::set_mouse_mode(MouseMode mode)
{
    d_mouse_mode = mode;
}


void GridWidget::request_render_update()
{
    update();
}


QPoint GridWidget::snap_to_grid(QPoint const &point, bool round)
{
    int rounder = round ? 32 : 0;
    
    int x = point.x() + rounder;
    int y = point.y() + rounder;
    // below 0 shit gets fucky wucky, which we fix like this
    if (x < 0) x -= 64;
    if (y < 0) y -= 64;
    x = (x / 64) * 64;
    y = (y / 64) * 64;

    return QPoint{x, y};
}


QPoint GridWidget::world_pos(QPoint const &point)
{
    return QPoint{point.x() - d_offset.x(), point.y() - d_offset.y()};
}


void GridWidget::reset_offset()
{
    d_offset = {};
    update();
}

////////////////////
//  Mouse Events  //
////////////////////

void GridWidget::mouseMoveEvent(QMouseEvent *event)
{
    bool shift = (event->modifiers() & Qt::ShiftModifier) != 0;
    int dx = event->x() - d_mouse_old.x();
    int dy = event->y() - d_mouse_old.y();
    
    if (d_right_button)
    {
        d_offset.setX(d_offset.x() + dx);
        d_offset.setY(d_offset.y() + dy);
    }

    if (d_left_button)
    {
        switch (d_mouse_mode)
        {
            case MouseMode::MOVE_GRID:
                d_offset.setX(d_offset.x() + dx);
                d_offset.setY(d_offset.y() + dy);
            break;

            case MouseMode::LINE_DRAW:
                d_line_end = shift ? snap_to_grid(world_pos(event->pos())) : world_pos(event->pos());
            break;

            case MouseMode::FREE_DRAW:
                d_line_segments.push_back({d_worldmouse_old, world_pos(event->pos())});
            break;

            default: break;
        }
    }

    d_worldmouse_old = world_pos(event->pos());
    d_mouse_old = event->pos();

    update();
}


void GridWidget::mousePressEvent(QMouseEvent *event)
{
    bool shift = (event->modifiers() & Qt::ShiftModifier) != 0;

    switch (event->button())
    {
        case Qt::LeftButton:
            d_left_button = true;
            
            switch (d_mouse_mode)
            {
                case MouseMode::LINE_DRAW:
                    d_line_start = shift ? snap_to_grid(world_pos(event->pos())) : world_pos(event->pos());
                break;

                default: break;
            }
        break;
        
        case Qt::RightButton:
            d_right_button = true;
        break;

        default: break;
    }
}


void GridWidget::mouseReleaseEvent(QMouseEvent *event)
{
    bool shift = (event->modifiers() & Qt::ShiftModifier) != 0;

    switch (event->button())
    {
        case Qt::LeftButton:
            d_left_button = false;
            switch (d_mouse_mode)
            {
                case MouseMode::MOVE_CHARACTER:
                    emit grid_player_move(snap_to_grid(world_pos(event->pos()), false));
                break;

                case MouseMode::LINE_DRAW:
                {
                    QPoint end = shift ? snap_to_grid(world_pos(event->pos())) : world_pos(event->pos());
                    emit grid_line_drawn({{d_line_start, end}}, d_draw_color);
                }
                break;

                case MouseMode::FREE_DRAW:
                    emit grid_line_drawn(d_line_segments, d_draw_color);
                    d_line_segments.clear();
                break;

                default: break;
            }
        break;
        
        case Qt::RightButton:
            d_right_button = false;
        break;

        default: break;
    }
}
