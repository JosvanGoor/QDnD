#include "gridwidget.h"

////////////////////
//  Constructors  //
////////////////////

GridWidget::GridWidget(QWidget *parent)
:   QWidget(parent)
{
    d_gridsize = 64;
    d_offset = {};
    d_mouse_old = {};
    d_grid_model = nullptr;
}


GridWidget::~GridWidget()
{

}


////////////////////
//    Painting    //
////////////////////

void GridWidget::paintEvent([[maybe_unused]] QPaintEvent *event)
{
    QPainter painter{this};

    painter.fillRect(0, 0, width(), height(), QBrush{background_color()});
    paint_grid(painter);
}


void GridWidget::paint_grid(QPainter &painter)
{
    painter.setPen(QPen{foreground_color()});

    int offset_x = d_offset.x() % d_gridsize;
    int offset_y = d_offset.y() % d_gridsize;

    for (int col = offset_x; col < width(); col += d_gridsize)
        painter.drawLine(col, 0, col, height());

    for (int row = offset_y; row < height(); row += d_gridsize)
        painter.drawLine(0, row, width(), row);
}


////////////////////
//    Utility     //
////////////////////

QColor GridWidget::foreground_color()
{
    return !d_grid_model ? QColor{Qt::black} : d_grid_model->foreground_color();
}


QColor GridWidget::background_color()
{
    return !d_grid_model ? QColor{Qt::white} : d_grid_model->background_color();
}