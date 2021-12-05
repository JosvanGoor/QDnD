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


void paint_player(QPainter &painter, QPixmap const &pixmap, GridScale size, QPoint pos, QPoint offset)
{
    int dims = 64 * scale(size);
    painter.translate(offset);
    painter.drawPixmap({pos.x(), pos.y(), dims, dims}, pixmap);
    painter.resetTransform();
}


void paint_line(QPainter &painter, QVector<QLine> const &lines, QColor color, QPoint offset)
{
    painter.translate(offset);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(8);
    painter.setPen(pen);

    painter.drawLines(lines);
    painter.resetTransform();
}