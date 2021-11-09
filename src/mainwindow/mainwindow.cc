#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
:   QMainWindow(parent)
{
    setCentralWidget(new GridWidget);
}


MainWindow::~MainWindow()
{

}