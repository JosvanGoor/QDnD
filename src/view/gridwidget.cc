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
    if (d_mouse_mode == MouseMode::LINE_DRAW && d_left_button)
    {
        QPen pen;
        pen.setColor(d_draw_color);
        pen.setWidth(8);

        painter.translate(d_offset);
        painter.setPen(pen);
        painter.drawLine(d_line_start, d_line_end);
        painter.resetTransform();
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


QPoint GridWidget::snap_to_grid(QPoint const &point)
{
    return QPoint{((point.x() + 32) / 64) * 64, ((point.y() + 32) / 64) * 64};
}


QPoint GridWidget::world_pos(QPoint const &point)
{
    return QPoint{point.x() - d_offset.x(), point.y() - d_offset.y()};
}

////////////////////
//  Mouse Events  //
////////////////////

void GridWidget::mouseMoveEvent(QMouseEvent *event)
{
    bool shift = (event->modifiers() & Qt::ShiftModifier) != 0;
    int dx = event->x() - d_mouse_old.x();
    int dy = event->y() - d_mouse_old.y();
    d_mouse_old = event->pos();

    if (d_right_button || (d_left_button && d_mouse_mode == MouseMode::MOVE_GRID))
    {
        d_offset.setX(d_offset.x() + dx);
        d_offset.setY(d_offset.y() + dy);
    }

    if (d_mouse_mode == MouseMode::LINE_DRAW)
    {
        d_line_end = shift ? snap_to_grid(world_pos(event->pos())) : world_pos(event->pos());
    }

    update();
}


void GridWidget::mousePressEvent(QMouseEvent *event)
{
    bool shift = (event->modifiers() & Qt::ShiftModifier) != 0;

    switch (event->button())
    {
        case Qt::LeftButton:
            d_left_button = true;
            if (d_mouse_mode == MouseMode::LINE_DRAW)
                d_line_start = shift ? snap_to_grid(world_pos(event->pos())) : world_pos(event->pos());
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
            if (d_mouse_mode == MouseMode::MOVE_CHARACTER)
            {
                int x = (event->x() - d_offset.x());
                int y = (event->y() - d_offset.y());
                if (x < 0) x -= 64;
                if (y < 0) y -= 64;
                x = (x / 64) * 64;
                y = (y / 64) * 64;
                grid_player_move({x, y});
            }
            else if (d_mouse_mode == MouseMode::LINE_DRAW)
            {
                QVector<QLine> lines;
                QPoint end = shift ? snap_to_grid(world_pos(event->pos())) : world_pos(event->pos());
                lines.push_back({d_line_start, end});
                emit grid_line_drawn(lines, d_draw_color);
            }
        break;
        
        case Qt::RightButton:
            d_right_button = false;
        break;

        default: break;
    }
}
