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
    }
}


void GridWidget::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
            d_left_button = false;
        break;
        
        case Qt::RightButton:
            d_right_button = false;
        break;
    }
}