#ifndef UTILITY_PAINTING_H
#define UTILITY_PAINTING_H

#include <QPainter>
#include <QPoint>
#include <QSize>

#include "enums.h"

void paint_grid(QPainter &painter, QSize size, QPoint offset);
void paint_player(QPainter &painter, QPixmap const &pixmap, GridScale size, QPoint pos, QPoint offset);
void paint_line(QPainter &painter, QVector<QLine> const &lines, QColor color, QPoint offset);
void paint_rect_around_line(QPainter &painter, QVector<QLine> const &lines, QColor color, QPoint offset);
void paint_rect_around_pixmap(QPainter &painter, QPoint const &pos, GridScale scale, QColor color, QPoint offset);

#endif