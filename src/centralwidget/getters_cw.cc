#include "centralwidget.h"

DisplayWidget *CentralWidget::display_widget()
{
    return d_display_tab;
}


DisplayControlWidget *CentralWidget::display_control_widget()
{
    return d_display_control;
}


GridWidget *CentralWidget::grid_widget()
{
    return d_grid_tab;
}


void CentralWidget::add_monster_control()
{
    d_right_tabs->addTab(d_monster_control = new MonsterControlWidget, "Monster Control");
}


MonsterControlWidget *CentralWidget::monster_control()
{
    return d_monster_control;
}


TextWidget *CentralWidget::text_widget()
{
    return d_text_tab;
}


UsersWidget *CentralWidget::user_widget()
{
    return d_users_tab;
}