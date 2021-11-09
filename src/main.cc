#include "mainwindow/mainwindow.h"
#include "startupwindow/startupwindow.h"

#include <QApplication>

int main(int argv, char *argc[])
{
    QApplication app(argv, argc);

    // StartupWindow window;
    // window.show();

    MainWindow *window = new MainWindow;
    window->show();

    app.exec();
}