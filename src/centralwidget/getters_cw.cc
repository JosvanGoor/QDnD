#include "centralwidget.h"

DisplayWidget *CentralWidget::display_widget()
{
    return d_display_tab;
}


DisplayControlWidget *CentralWidget::display_control_widget()
{
    return d_display_control;
}


TextWidget *CentralWidget::text_widget()
{
    return d_text_tab;
}