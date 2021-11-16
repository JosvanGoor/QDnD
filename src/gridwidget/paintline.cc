#include "gridwidget.h"

void GridWidget::paint_line(QPainter *painter, QVector<QLine> const &lines, QColor color)
{
    QPen pen{color};
    pen.setWidth(8);
    painter->setPen(pen);
    painter->translate(QPoint{d_offset_x, d_offset_y});
    painter->drawLines(lines);
    painter->translate(QPoint{-d_offset_x, -d_offset_y});
}


void GridWidget::paint_current_line(QPainter *painter)
{
    paint_line(painter, d_current_line, Qt::black);
}


void GridWidget::paint_line_cache(QPainter *painter)
{
    for (auto it = d_line_cache.begin(); it != d_line_cache.end(); ++it)
    {
        QColor color = d_control->is_selected(it.key()) ? Qt::green : it.value().color;
        paint_line(painter, it.value().line, color);
    }
}


void GridWidget::add_line(QString const &name, QColor const &color, QVector<QLine> const &line)
{
    d_line_cache[name] = {line, color};
    d_control->add_line(name);
    update();
}


void GridWidget::remove_line(QString const &name)
{
    std::cout << "remove_line for name " << name.toStdString() << "\n";
    d_line_cache.remove(name);
    line_removed(name);
    update();
}


void GridWidget::silent_remove_line(QString const &name)
{
    d_line_cache.remove(name);
    d_control->remove_entry_by_name(name);
    update();
}