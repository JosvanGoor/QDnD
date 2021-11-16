#include "gridwidget.h"

void GridWidget::paintEvent([[maybe_unused]] QPaintEvent *event)
{
    QPainter painter{this};
    QSize canvas_size = size();
    
    painter.fillRect(0, 0, canvas_size.width(), canvas_size.height(), QBrush{Qt::white});

    paint_grid(&painter);
    paint_current_line(&painter);
    paint_line_cache(&painter);
    paint_avatars(&painter);
}