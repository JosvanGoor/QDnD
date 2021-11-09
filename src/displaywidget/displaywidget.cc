#include "displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent)
:   QWidget(parent)
{
    d_current_display = QPixmap{":data/display_default.jpg"};
}


DisplayWidget::~DisplayWidget()
{

}