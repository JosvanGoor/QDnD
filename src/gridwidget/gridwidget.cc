#include "gridwidget.h"

GridWidget::GridWidget(GridControlWidget *control, QWidget *parent)
:   QWidget(parent)
{
    d_scale = 1.0f;
    d_gridsize = 64;
    d_offset_x = 256 * d_gridsize;
    d_offset_y = 256 * d_gridsize;
    d_foreground_color = QColor{75, 75, 75}; // black
    d_background_color = QColor{255, 255, 255}; // white
    d_mouse_old_position = QPoint{};
    d_right_mouse_button_down = false;
    d_left_mouse_button_down = false;
    d_control = control;
    d_controlled_avatar = "Jos"; ///////

    setMinimumSize({12 * d_gridsize, 12 * d_gridsize});

    QObject::connect
    (
        d_control,
        &GridControlWidget::delete_line,
        this,
        &GridWidget::remove_line
    );

    QObject::connect
    (
        d_control,
        &GridControlWidget::on_reset_position,
        this,
        &GridWidget::on_reset_position
    );
}