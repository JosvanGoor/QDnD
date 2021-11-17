#include "control/applicationcontrol.h"
#include <QApplication>

int main(int argv, char *argc[])
{
    QApplication application{argv, argc};
    ApplicationControl application_control;
    return application.exec();
}