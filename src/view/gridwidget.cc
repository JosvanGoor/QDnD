#include "gridwidget.h"

////////////////////
//  Constructors  //
////////////////////

GridWidget::GridWidget(QWidget *parent)
:   QWidget(parent)
{
    d_gridsize = 64;
    d_offset = {};
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
}


////////////////////
//    Utility     //
////////////////////

void GridWidget::set_mouse_mode(MouseMode mode)
{
    d_mouse_mode = mode;
}


void GridWidget::request_render_update()
{
    update();
}


////////////////////
//  Mouse Events  //
////////////////////

void GridWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - d_mouse_old.x();
    int dy = event->y() - d_mouse_old.y();
    d_mouse_old = event->pos();

    if (d_right_button || (d_left_button && d_mouse_mode == MouseMode::MOVE_GRID))
    {
        d_offset.setX(d_offset.x() + dx);
        d_offset.setY(d_offset.y() + dy);
    }
    update();
}


void GridWidget::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
            d_left_button = true;
        break;
        
        case Qt::RightButton:
            d_right_button = true;
        break;

        default: break;
    }
}


void GridWidget::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
            d_left_button = false;
            if (d_mouse_mode == MouseMode::MOVE_CHARACTER)
            {
                int x = (event->x() - d_offset.x());
                int y = (event->y() - d_offset.y());

                if (x < 0)
                    x -= 64;
                if (y < 0)
                    y -= 64;
                
                x = (x / d_gridsize) * d_gridsize;
                y = (y / d_gridsize) * d_gridsize;

                grid_player_move({x, y});
            }
        break;
        
        case Qt::RightButton:
            d_right_button = false;
        break;

        default: break;
    }
}
