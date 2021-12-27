#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <QSplitter>
#include <QTabWidget>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextEdit>

#include "chatwidget.h"
#include "displaywidget.h"
#include "entitywidget.h"
#include "gridcontrolwidget.h"
#include "gridwidget.h"
#include "itemgroupcontrolwidget.h"
#include "mapmanagercontrolwidget.h"
#include "menubar.h"
#include "playerswidget.h"
#include "spellswidget.h"
#include "statusbar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QSplitter *d_central_widget;
        QSplitter *d_middle_widget;
            QTabWidget *d_middle_tabs;
                DisplayWidget *d_display_tab;
                SpellsWidget *d_spells_tab;
                GridWidget *d_grid_tab;
            QTextEdit *d_debug_output;
        QTabWidget *d_right_tabs;
            ChatWidget *d_chat_tab;
            PlayersWidget *d_players_tab;
            GridControlWidget *d_grid_control_tab;
            EntityWidget *d_entity_tab;
            
        MapManagerControlWidget *d_map_manager;
        ItemGroupControlWidget *d_item_group_manager;
            

    MenuBar *d_menu_bar;
    StatusBar *d_status_bar;

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        // getters
        ChatWidget *chat_widget() noexcept;
        DisplayWidget *display_widget() noexcept;
        EntityWidget *entity_widget() noexcept;
        GridControlWidget *grid_control_widget() noexcept;
        GridWidget *grid_widget() noexcept;
        MenuBar *menu_bar() noexcept;
        PlayersWidget *players_widget() noexcept;
        SpellsWidget *spells_widget() noexcept;
        StatusBar *status_bar() noexcept;
        ItemGroupControlWidget *item_group_control() noexcept;

        // editor
        void load_editor(MapManager *manager);
        void unload_editor();

    public slots:
        void debug_message(QString const &message);
        void right_tab_changed(int index);
};

#endif