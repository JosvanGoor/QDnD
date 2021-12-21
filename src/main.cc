#include <QApplication>

#include <iostream>

#include "control/applicationcontrol.h"

int main(int argv, char *argc[])
{
    QApplication application{argv, argc};

    std::cout << sizeof(QOpenGLFunctions_4_5_Core) << "\n";

    ApplicationControl control;

    return application.exec();
}