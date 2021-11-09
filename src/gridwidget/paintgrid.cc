#include "gridwidget.h"

void GridWidget::paint_grid(QPainter *painter)
{
    size_t gridsize = d_gridsize * d_scale;
    size_t offset_x = static_cast<size_t>(d_offset_x * d_scale) % gridsize;
    size_t offset_y = static_cast<size_t>(d_offset_y * d_scale) % gridsize;

    painter->setBrush(QBrush{d_foreground_color});

    // paint vertical
    for (size_t xpos = offset_x; xpos < size().width(); xpos += gridsize)
        painter->drawLine(xpos, 0, xpos, size().height());

    for (size_t ypos = offset_y; ypos < size().height(); ypos += gridsize)
        painter->drawLine(0, ypos, size().width(), ypos);
}