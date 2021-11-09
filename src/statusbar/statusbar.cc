#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent)
:   QStatusBar(parent)
{
    d_connection_status = new QLabel{"No Connection."};
    addPermanentWidget(d_connection_status);
}


StatusBar::~StatusBar()
{

}