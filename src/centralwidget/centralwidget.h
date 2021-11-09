#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QSplitter>
#include <QTabWidget>

#include "../displaywidget/displaywidget.h"
#include "../gridwidget/gridwidget.h"
#include "../spellswidget/spellswidget.h"
#include "../textwidget/textwidget.h"

class CentralWidget : public QSplitter
{
    Q_OBJECT

    QTabWidget *d_left_tabs;
        DisplayWidget *d_display_tab;
        SpellsWidget *d_spells_tab;
        GridWidget *d_grid_tab;
    QTabWidget *d_right_tabs;
        TextWidget *d_text_tab;

    public:
        explicit CentralWidget(QWidget *parent = nullptr);
        ~CentralWidget();
};

#endif