#include "gridwidget.h"

void GridWidget::paint_grid(QPainter *painter)
{
    int gridsize = d_gridsize * d_scale;
    int offset_x = static_cast<int>(d_offset_x * d_scale) % gridsize;
    int offset_y = static_cast<int>(d_offset_y * d_scale) % gridsize;

    painter->setPen(QPen{d_foreground_color});

    // paint vertical
    for (int xpos = offset_x; xpos < size().width(); xpos += gridsize)
        painter->drawLine(xpos, 0, xpos, size().height());

    for (int ypos = offset_y; ypos < size().height(); ypos += gridsize)
        painter->drawLine(0, ypos, size().width(), ypos);
}