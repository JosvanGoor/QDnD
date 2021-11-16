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
            if (!d_current_line.empty())
            {
                line_drawn(d_current_line);
                d_current_line.clear();
                update();
            }

            if (!d_control->is_drawing() && !d_controlled_avatar.isEmpty()) // moving avatar
            {
                int xpos = ((event->x() - d_offset_x) / 64) * 64;
                int ypos = ((event->y() - d_offset_y) / 64) * 64;

                d_avatars[d_controlled_avatar].position = {xpos, ypos};
                avatar_moved(d_controlled_avatar, {xpos, ypos});
                update();
            }
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
    
    if (d_right_mouse_button_down)
    {
        // the scaling is not perfect but "good enough" for now.
        d_offset_x += diffx * (1.0 / d_scale);
        d_offset_y += diffy * (1.0 / d_scale);
        update();
    }
    else if (d_control->is_drawing() && d_left_mouse_button_down)
    {
        QPoint old_pos{d_mouse_old_position.x() - d_offset_x, d_mouse_old_position.y() - d_offset_y};
        QPoint new_pos{event->x() - d_offset_x, event->y() - d_offset_y};

        d_current_line.append(QLine{old_pos, new_pos});
        update();
    }

    d_mouse_old_position = event->pos();
    event->accept();
}


// void GridWidget::keyReleaseEvent(QKeyEvent *event)
// {
//     if (event->key() == Qt::Key_Space)
//     {
//         d_offset_x = 0;
//         d_offset_y = 0;
//         update();
//     }
// }