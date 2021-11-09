#include "gridwidget.h"

void GridWidget::set_scale(float scale) noexcept
{
    d_scale = scale;
    update();
}


void GridWidget::set_gridsize(size_t gridsize) noexcept
{
    d_gridsize = gridsize;
    update();
}


void GridWidget::set_foreground_color(QColor const &color) noexcept
{
    d_foreground_color = color;
    update();
}


void GridWidget::set_background_color(QColor const &color) noexcept
{
    d_background_color = color;
    update();
}

