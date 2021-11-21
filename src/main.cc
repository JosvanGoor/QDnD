#include "control/applicationcontrol.h"
#include <QApplication>

#include <iostream>
#include "expressions/diceparser.h"
#include "expressions/dicetokenizer.h"

int main(int argv, char *argc[])
{
    QApplication application{argv, argc};
    ApplicationControl application_control;
    return application.exec();
}