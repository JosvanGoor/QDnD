#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>

#include "../centralwidget/centralwidget.h"
#include "../menubar/menubar.h"
#include "../statusbar/statusbar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    MenuBar *d_menu_bar;
    CentralWidget *d_central_widget;
    StatusBar *d_status_bar;

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
};

#endif