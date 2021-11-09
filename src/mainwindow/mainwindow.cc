#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
:   QMainWindow(parent)
{
    d_menu_bar = new MenuBar;
    setMenuBar(d_menu_bar);

    d_central_widget = new CentralWidget;
    setCentralWidget(d_central_widget);

    d_status_bar = new StatusBar;
    setStatusBar(d_status_bar);
}


MainWindow::~MainWindow()
{

}