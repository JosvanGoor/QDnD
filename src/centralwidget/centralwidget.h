#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QSpacerItem>
#include <QSplitter>
#include <QTabWidget>

#include "../displaywidget/displaywidget.h"
#include "../gridcontrolwidget/gridcontrolwidget.h"
#include "../gridwidget/gridwidget.h"
#include "../spellswidget/spellswidget.h"
#include "../textwidget/textwidget.h"
#include "../userswidget/userswidget.h"

class CentralWidget : public QSplitter
{
    Q_OBJECT

    QTabWidget *d_left_tabs;
        DisplayWidget *d_display_tab;
        SpellsWidget *d_spells_tab;
        GridWidget *d_grid_tab;
    QTabWidget *d_right_tabs;
        TextWidget *d_text_tab;
        UsersWidget *d_users_tab;
        QWidget *d_control_tab;
            GridControlWidget *d_grid_control;
            DisplayControlWidget *d_display_control;


    public:
        explicit CentralWidget(QWidget *parent = nullptr);
        ~CentralWidget();

        DisplayWidget *display_widget();
        DisplayControlWidget *display_control_widget();
        GridWidget *grid_widget();
        TextWidget *text_widget();
        UsersWidget *user_widget();
};

#endif