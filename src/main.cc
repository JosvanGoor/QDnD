#include <QApplication>
#include <random>

#include "control/applicationcontrol.h"

int main(int argv, char *argc[])
{
    srand(time(nullptr));
    QApplication application{argv, argc};

    ApplicationControl control;

    return application.exec();
}