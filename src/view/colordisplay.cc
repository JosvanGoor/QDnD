#include "colordisplay.h"

////////////////////
//  Constructors  //
////////////////////

ColorDisplay::ColorDisplay(QColor color, QWidget *parent)
:   QWidget(parent)
{
    d_color = color;
}


ColorDisplay::~ColorDisplay()
{

}


////////////////////
//   Set / Get    //
////////////////////

QColor ColorDisplay::color()
{
    return d_color;
}


void ColorDisplay::set_color(QColor color)
{
    d_color = color;
}


////////////////////
//   paintEvent   //
////////////////////

void ColorDisplay::paintEvent(QPaintEvent *event)
{
    QPainter painter{this};
    painter.fillRect(QRect{0, 0, width(), height()}, d_color);
    event->accept();
}