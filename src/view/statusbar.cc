#include "statusbar.h"

////////////////////
//  Constructors  //
////////////////////

StatusBar::StatusBar(QWidget *parent)
:   QStatusBar(parent)
{
    addPermanentWidget(d_connection_status = new QLabel{"No Connection."});
}


StatusBar::~StatusBar()
{

}


////////////////////
//     Slots      //
////////////////////

void StatusBar::update_connection_status(QString const &message)
{
    d_connection_status->setText(message);
}


void StatusBar::status_message(QString const &message, int timeout_ms)
{
    if (timeout_ms == 0)
        timeout_ms = 10000; // 5 sec

    showMessage(message, timeout_ms);
}