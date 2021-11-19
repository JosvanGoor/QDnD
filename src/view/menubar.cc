#include "menubar.h"

////////////////////
//  Constructors  //
////////////////////

MenuBar::MenuBar(QWidget *parent)
:   QMenuBar(parent)
{
    addMenu(d_file = new QMenu{"File"});
    d_file->addAction(d_quit = new QAction{"Quit"});

    addMenu(d_connection = new QMenu{"Connection"});
    d_connection->addAction(d_host = new QAction{"Host"});
    d_connection->addAction(d_connect = new QAction{"Connect"});
    d_connection->addSeparator();
    d_connection->addAction(d_disconnect = new QAction{"Disconnect"});
}


MenuBar::~MenuBar()
{

}


////////////////////
//    Getters     //
////////////////////

QAction *MenuBar::quit()
{
    return d_quit;
}


QAction *MenuBar::host()
{
    return d_host;
}


QAction *MenuBar::connect()
{
    return d_connect;
}


QAction *MenuBar::disconnect()
{
    return d_disconnect;
}