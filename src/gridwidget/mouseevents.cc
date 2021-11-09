#include "gridwidget.h"

void GridWidget::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::LeftButton:
            d_left_mouse_button_down = true;
            d_mouse_old_position = event->pos();
        break;

        case Qt::RightButton:
            d_right_mouse_button_down = true;
            d_mouse_old_position = event->pos();
        break;

        default: break;
    }

    event->accept();
}


void GridWidget::mouseReleaseEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::LeftButton:
            d_left_mouse_button_down = false;
        break;

        case Qt::RightButton:
            d_right_mouse_button_down = false;
        break;

        default: break;
    }

    event->accept();
}


void GridWidget::mouseMoveEvent(QMouseEvent *event)
{
    int diffx = event->x() - d_mouse_old_position.x();
    int diffy = event->y() - d_mouse_old_position.y();
    d_mouse_old_position = event->pos();

    if (d_right_mouse_button_down)
    {
        // the scaling is not perfect but "good enough" for now.
        d_offset_x += diffx * (1.0 / d_scale);
        d_offset_y += diffy * (1.0 / d_scale);
        update();
    }

    event->accept();
}


void GridWidget::wheelEvent(QWheelEvent *event)
{
    int steps = event->angleDelta().y() / 120.0f;
    
    d_scale = d_scale + (0.1 * steps);
    d_scale = d_scale < 0.1f ? 0.1f : d_scale;

    update();

    event->accept();
}