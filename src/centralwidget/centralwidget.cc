#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent)
:   QSplitter(parent)
{
    d_display_tab = new DisplayWidget;
    d_spells_tab = new SpellsWidget;
    d_grid_tab = new GridWidget;
    d_text_tab = new TextWidget;

    d_left_tabs = new QTabWidget;
    d_left_tabs->addTab(d_display_tab, "Display");
    d_left_tabs->addTab(d_spells_tab, "Spells");
    d_left_tabs->addTab(d_grid_tab, "Grid");

    d_right_tabs = new QTabWidget;
    d_right_tabs->addTab(d_text_tab, "Chat");

    addWidget(d_left_tabs);
    addWidget(d_right_tabs);
    setSizes({600, 300});
}


CentralWidget::~CentralWidget()
{
    
}