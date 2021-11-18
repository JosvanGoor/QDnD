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
#include "spellswidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QSplitter *d_central_widget;
        QSplitter *d_middle_widget;
            QTabWidget *d_middle_tabs;
                SpellsWidget *d_spells_tab;
            QTextEdit *d_debug_output;
        QTabWidget *d_left_tabs;
            ChatWidget *d_chat_tab;
        
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        // getters
        SpellsWidget *spells_widget() noexcept;
        ChatWidget *chat_widget() noexcept;

    public slots:
        void debug_message(QString const &message);
};

#endif