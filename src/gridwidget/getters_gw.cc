#include "gridwidget.h"

float GridWidget::scale() const noexcept
{
    return d_scale;
}


size_t GridWidget::gridsize() const noexcept
{
    return d_gridsize;
}


QColor const &GridWidget::foreground_color() const noexcept
{
    return d_foreground_color;
}


QColor const &GridWidget::background_color() const noexcept
{
    return d_background_color;
}

