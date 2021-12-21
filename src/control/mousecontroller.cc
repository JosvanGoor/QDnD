#include "mousecontroller.h"

////////////////////
//  Constructor   //
////////////////////

MouseController::MouseController(QObject *parent)
:   QObject(parent)
{
    d_zoom = 1.0f;
    d_widget_size = {};
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
    regenerate_ortho();
}


void MouseController::grid_resized(QSize const &size)
{
    d_widget_size = size;
    regenerate_ortho();
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
//    Setters     //
////////////////////

void MouseController::set_entity_mode(bool mode)
{
    d_entity_mode = mode;
}


void MouseController::set_mouse_mode(MouseMode mode)
{
    d_mouse_mode = mode;
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
        d_grid_offset = {d_grid_offset.x() - dx, d_grid_offset.y() + dy};
        regenerate_ortho();
    }

    d_old_position = event->pos();
}


void MouseController::mouse_wheel_event(QWheelEvent *event)
{
    int steps = event->angleDelta().y() / (8 * 15);
    d_zoom -= 0.1 * steps;
    d_zoom = qMax(0.5f, d_zoom);
    d_zoom = qMin(2.0f, d_zoom);
    regenerate_ortho();
}


void MouseController::regenerate_ortho()
{
    d_grid_size = d_widget_size * d_zoom;

    float left = d_grid_offset.x();
    float right = d_grid_size.width() + d_grid_offset.x();
    float top = d_grid_offset.y();
    float bottom = d_grid_size.height() + d_grid_offset.y();
    
    emit ortho_changed(left, right, top, bottom);
}