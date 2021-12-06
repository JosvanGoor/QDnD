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


void paint_rect_around_line(QPainter &painter, QVector<QLine> const &lines, QColor color, QPoint offset)
{
    int max_x = -1'000'000;
    int min_x = 1'000'000;
    int max_y = -1'000'000;
    int min_y = 1'000'000;

    for (auto &line : lines)
    {
        max_x = qMax(qMax(max_x, line.x1()), line.x2());
        max_y = qMax(qMax(max_y, line.y1()), line.y2());
        min_x = qMin(qMin(min_x, line.x1()), line.x2());
        min_y = qMin(qMin(min_y, line.y1()), line.y2());
    }

    max_x += 4;
    max_y += 4;
    min_x -= 4;
    min_y -= 4;

    painter.translate(offset);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(2);
    painter.setPen(pen);

    painter.drawRect(min_x, min_y, max_x - min_x, max_y - min_y);
    painter.resetTransform();
}


void paint_rect_around_pixmap(QPainter &painter, QPoint const &pos, GridScale size, QColor color, QPoint offset)
{
    int dims = 64 * scale(size);

    QPen pen;
    pen.setColor(color);
    pen.setWidth(2);

    painter.setPen(pen);
    painter.translate(offset);
    painter.drawRect(pos.x(), pos.y(), dims, dims);
    painter.resetTransform();
}