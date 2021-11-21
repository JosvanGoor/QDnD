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

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QSplitter *d_central_widget;
        QSplitter *d_middle_widget;
            QTabWidget *d_middle_tabs;
                DisplayWidget *d_display_tab;
                SpellsWidget *d_spells_tab;
            QTextEdit *d_debug_output;
        QTabWidget *d_right_tabs;
            PlayersWidget *d_players_widget;
            ChatWidget *d_chat_tab;

    
    MenuBar *d_menu_bar;
    StatusBar *d_status_bar;

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        // getters
        ChatWidget *chat_widget() noexcept;
        MenuBar *menu_bar() noexcept;
        PlayersWidget *players_widget() noexcept;
        SpellsWidget *spells_widget() noexcept;
        StatusBar *status_bar() noexcept;

    public slots:
        void debug_message(QString const &message);
};

#endif