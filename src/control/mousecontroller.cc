#include "mousecontroller.h"

////////////////////
//  Constructor   //
////////////////////

MouseController::MouseController(QObject *parent)
:   QObject(parent)
{
    d_grid_size = {};
    d_grid_offset = {};
    d_entity_mode = false;
    d_mouse_mode = MouseMode::MOVE_CHARACTER;
    d_left_mouse_button = false;
    d_right_mouse_button = false;
}


MouseController::~MouseController()
{ }


////////////////////
//    Utility     //
////////////////////

void MouseController::reset_offset()
{
    d_grid_offset = {0, 0};
}


void MouseController::grid_resized(int width, int height)
{
    d_grid_size = {width, height};
}



////////////////////
//    Getters     //
////////////////////

QSize const &MouseController::grid_size()
{
    return d_grid_size;
}


QPoint const &MouseController::grid_offset()
{
    return d_grid_offset;
}


////////////////////
//     Events     //
////////////////////

void MouseController::mouse_press_event(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
            d_left_mouse_button = true;
        break;

        case Qt::RightButton:
            d_right_mouse_button = true;
        break;

        default: break;
    }
}


void MouseController::mouse_release_event(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
            d_left_mouse_button = false;
        break;

        case Qt::RightButton:
            d_right_mouse_button = false;
        break;

        default: break;
    }
}


void MouseController::mouse_move_event(QMouseEvent *event)
{
    int dx = event->x() - d_old_position.x();
    int dy = event->y() - d_old_position.y();

    if (d_right_mouse_button)
    {
        d_grid_offset = {d_grid_offset.x() + dx, d_grid_offset.y() + dy};
        emit ortho_changed(d_grid_offset.x(), d_grid_offset.y(), d_grid_size.width(), d_grid_size.height());
        emit debug_message("new grid offset: [" + QString::number(d_grid_offset.x()) + ", " + QString::number(d_grid_offset.y()) + "]");
    }

    d_old_position = event->pos();
}


void MouseController::mouse_wheel_event(QWheelEvent *event)
{

}