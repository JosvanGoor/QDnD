#include "painting.h"

void paint_grid(QPainter &painter, QSize size, QPoint offset)
{
    static const int gridsize = 64;

    int x_off = offset.x() % gridsize;
    int y_off = offset.y() % gridsize;

    for (int col = x_off; col < size.width(); col += gridsize)
        painter.drawLine(col, 0, col, size.height());

    for (int row = y_off; row < size.height(); row += gridsize)
        painter.drawLine(0, row, size.width(), row);
}