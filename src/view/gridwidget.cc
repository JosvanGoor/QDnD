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
    
    emit paint_ground_layer(painter, size(), d_offset, d_mouse_old);
    emit paint_player_layer(painter, size(), d_offset, d_mouse_old);
    emit paint_entity_layer(painter, size(), d_offset, d_mouse_old);
    emit paint_mouse_layer(painter, size(), d_offset, d_mouse_old);
}