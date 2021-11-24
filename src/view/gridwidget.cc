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

    painter.fillRect(0, 0, width(), height(), QBrush{Qt::white});
    paint_grid(painter);
}


void GridWidget::paint_grid(QPainter &painter)
{
    painter.setPen(QPen{Qt::black});

    int offset_x = d_offset.x() % d_gridsize;
    int offset_y = d_offset.y() % d_gridsize;

    for (int col = offset_x; col < width(); col += d_gridsize)
        painter.drawLine(col, 0, col, height());

    for (int row = offset_y; row < height(); row += d_gridsize)
        painter.drawLine(0, row, width(), row);
}