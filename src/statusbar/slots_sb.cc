#include "statusbar.h"

void StatusBar::update_connection_status(QString const &str)
{
    d_connection_status->setText(str);
}