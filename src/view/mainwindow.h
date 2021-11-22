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
#include "menubar.h"
#include "playerswidget.h"
#include "spellswidget.h"
#include "statusbar.h"
#include "../grid/gridbuilderwidget.h"
#include "../grid/gridwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QSplitter *d_central_widget;
        QSplitter *d_middle_widget;
            QTabWidget *d_middle_tabs;
                DisplayWidget *d_display_tab;
                SpellsWidget *d_spells_tab;
                GridWidget *d_grid_widget;
            QTextEdit *d_debug_output;
        QTabWidget *d_right_tabs;
            PlayersWidget *d_players_tab;
            ChatWidget *d_chat_tab;
            GridBuilderWidget *d_grid_builder_tab;

    MenuBar *d_menu_bar;
    StatusBar *d_status_bar;

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        // getters
        ChatWidget *chat_widget() noexcept;
        DisplayWidget *display_widget() noexcept;
        GridWidget *grid_widget() noexcept;
        MenuBar *menu_bar() noexcept;
        PlayersWidget *players_widget() noexcept;
        SpellsWidget *spells_widget() noexcept;
        StatusBar *status_bar() noexcept;

    public slots:
        void debug_message(QString const &message);
};

#endif