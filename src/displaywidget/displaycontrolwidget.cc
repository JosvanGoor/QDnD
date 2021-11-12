#include "displaywidget.h"

DisplayControlWidget::DisplayControlWidget(QWidget *parent)
:   QGroupBox("Display Control", parent)
{
    d_select_button = new QPushButton{"Set Image"};
    setLayout(new QVBoxLayout);
    layout()->addWidget(d_select_button);
}


DisplayControlWidget::~DisplayControlWidget()
{

}
