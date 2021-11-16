#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent)
:   QSplitter(parent)
{
    d_control_tab = new QWidget;
    d_control_tab->setLayout(new QVBoxLayout);
    d_grid_control = new GridControlWidget;
    d_display_control = new DisplayControlWidget;
    d_control_tab->layout()->addWidget(d_grid_control);
    d_control_tab->layout()->addWidget(d_display_control);

    d_display_tab = new DisplayWidget;
    d_spells_tab = new SpellsWidget;
    d_grid_tab = new GridWidget{d_grid_control};
    d_text_tab = new TextWidget;
    d_users_tab = new UsersWidget;

    d_left_tabs = new QTabWidget;
    d_left_tabs->addTab(d_display_tab, "Display");
    d_left_tabs->addTab(d_spells_tab, "Spells");
    d_left_tabs->addTab(d_grid_tab, "Grid");

    d_right_tabs = new QTabWidget;
    d_right_tabs->addTab(d_text_tab, "Chat");
    d_right_tabs->addTab(d_users_tab, "Connected");
    d_right_tabs->addTab(d_control_tab, "Control");

    addWidget(d_left_tabs);
    addWidget(d_right_tabs);
    setSizes({1300, 300});
}


CentralWidget::~CentralWidget()
{
    
}