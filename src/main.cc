#include <QApplication>

#include "control/applicationcontrol.h"

int main(int argv, char *argc[])
{
    QApplication application{argv, argc};

    ApplicationControl control;

    return application.exec();
}