#include "gridwidget.h"

////////////////////
//  Constructor   //
////////////////////

GridWidget::GridWidget(QWidget *parent)
:   QWidget(parent)
{
    d_offset_x = 0;
    d_offset_y = 0;
    d_mouse_left_button_down = false;
    d_mouse_right_button_down = false;

    setMouseTracking(true);
    setMinimumSize(12 * gridsize, 12 * gridsize);
}


GridWidget::~GridWidget()
{

}


////////////////////
//    Painting    //
////////////////////

void GridWidget::paintEvent(QPaintEvent *event)
{
    event->accept();

    QPainter painter{this};
    painter.fillRect(0, 0, width(), height(), Qt::white);
    
    d_mouse_state.paint_pixmap(painter);
    paint_grid(painter);
}


void GridWidget::paint_grid(QPainter &painter)
{
    int offset_x = d_offset_x % gridsize;
    int offset_y = d_offset_y % gridsize;

    painter.setPen(QPen{Qt::black});

    // paint vertical
    for (int col = offset_x; col < size().width(); col += gridsize)
        painter.drawLine(col, 0, col, size().height());

    for (int row = offset_y; row < size().height(); row += gridsize)
        painter.drawLine(0, row, size().width(), row);
}


////////////////////
//     Input      //
////////////////////

void GridWidget::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}


void GridWidget::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
}


void GridWidget::mouseMoveEvent(QMouseEvent *event)
{
    d_mouse_state.update_mouse_position(event);
    event->accept();
    update();
}

GridMouseState &GridWidget::mouse_state()
{
    return d_mouse_state;
}