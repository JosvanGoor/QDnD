#include "gridwidget.h"

////////////////////
//  Constructors  //
////////////////////

GridWidget::GridWidget(QWidget *parent)
:   QWidget(parent)
{
    d_zoom = 1.0f;
    d_offset = {};
    d_draw_color = Qt::black;
    d_line_start = {};
    d_worldmouse_old = {};
    d_mouse_old = {};
    d_mouse_mode = MouseMode::MOVE_CHARACTER;
    d_snap_horizontal = false;
    d_snap_vertical = false;
    d_left_button = false;
    d_right_button = false;

    d_gi_rotation = 0;
    d_gi_scale = GridScale::MEDIUM;

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
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setWindow(0, 0, int(width() * (d_zoom)), int(height() * (d_zoom)));
    painter.fillRect(0, 0, (width() * d_zoom) + 1,  int(height() * d_zoom) + 1, QBrush{Qt::white});

    emit paint_ground_layer(painter, size() * d_zoom, d_offset, d_mouse_old);
    emit paint_player_layer(painter, size() * d_zoom, d_offset, d_mouse_old);
    emit paint_entity_layer(painter, size() * d_zoom, d_offset, d_mouse_old);
    emit paint_mouse_layer(painter, size() * d_zoom, d_offset, d_mouse_old);

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
    else if (d_mouse_mode == MouseMode::GRID_ITEM_PLACEMENT)
    {
        paint_grid_item(painter, d_offset, d_gi_pixmap, d_gi_scale, grid_item_snap(d_mouse_old), d_gi_rotation);
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


void GridWidget::set_snap_modes(bool horizontal, bool vertical, bool xoff, bool yoff)
{
    d_snap_horizontal = horizontal;
    d_snap_vertical = vertical;
    d_snap_offset_x = xoff;
    d_snap_offset_y = yoff;
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
    return QPoint{int((point.x() + 0.5) * d_zoom) - d_offset.x(), int((point.y() + 0.5) * d_zoom) - d_offset.y()};
}


QPoint GridWidget::grid_item_snap(QPoint const &point)
{
    QPoint position = world_pos(point);
    int x = position.x();
    int y = position.y();

    if (d_snap_horizontal)
    {
        x += 32 * d_snap_offset_x;
        if (x < 0) x -= 64;
        x = (x / 64) * 64;
    }

    if (d_snap_vertical)
    {
        y += 32 * d_snap_offset_y;
        if (y < 0) y -= 64;
        y  = (y / 64) * 64;
    }

    if (d_snap_offset_x) x -= scale(d_gi_scale) * 64 / 2;
    if (d_snap_offset_y) y -= scale(d_gi_scale) * 64 / 2;
    
    return QPoint{x, y};
}


void GridWidget::reset_offset()
{
    d_offset = {};
    update();
}


////////////////////
//  Mouse Events  //
////////////////////

void GridWidget::update_gi_pixmap(QPixmap const &pixmap)
{
    d_gi_pixmap = pixmap;
}


void GridWidget::update_gi_rotation(int rotation)
{
    d_gi_rotation = rotation;
}


void GridWidget::update_gi_scale(GridScale scale)
{
    d_gi_scale = scale;
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
        d_offset.setX(d_offset.x() + (dx * d_zoom));
        d_offset.setY(d_offset.y() + (dy * d_zoom));
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

                case MouseMode::GRID_ITEM_PLACEMENT:
                    emit debug_message("GRID_ITEM_PLACEMENT *click*");
                    emit grid_item_placed(grid_item_snap(event->pos()));
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


void GridWidget::wheelEvent(QWheelEvent *event)
{
    int steps = event->angleDelta().y() / (8 * 15);

    d_zoom -= steps * 0.1;
    d_zoom = qMax(0.5f, qMin(2.0f, d_zoom));
    update();
}
