#include "gridwidget.h"

void GridWidget::paintEvent([[maybe_unused]] QPaintEvent *event)
{
    QPainter painter{this};
    
    QSize canvas_size = size();
    painter.setBackground(QBrush{d_background_color});
    painter.drawRect(0, 0, canvas_size.width(), canvas_size.height());

    paint_grid(&painter);
}