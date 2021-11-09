#include "gridwidget.h"

GridWidget::GridWidget(QWidget *parent)
:   QWidget(parent)
{
    d_scale = 1.0f;
    d_gridsize = 64;
    d_offset_x = 0;
    d_offset_y = 0;
    d_foreground_color = QColor{0, 0, 0}; // black
    d_background_color = QColor{1, 1, 1}; // white
    d_mouse_old_position = QPoint{};
    d_right_mouse_button_down = false;
    d_left_mouse_button_down = false;

    setMinimumSize({12 * d_gridsize, 12 * d_gridsize});
}