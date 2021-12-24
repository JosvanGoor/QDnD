#include "menubar.h"

////////////////////
//  Constructors  //
////////////////////

MenuBar::MenuBar(QWidget *parent)
:   QMenuBar(parent)
{
    addMenu(d_file = new QMenu{"File"});
    d_file->addAction(d_load_lines = new QAction{"Load Lines"});
    d_file->addAction(d_save_own_lines = new QAction{"Save Own Lines"});
    d_file->addAction(d_save_all_lines = new QAction{"Save All Lines"});
    d_file->addSeparator();
    d_file->addAction(d_update_display = new QAction{"Update Display"});
    d_file->addSeparator();
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


QAction *MenuBar::update_display()
{
    return d_update_display;
}


QAction *MenuBar::load_lines()
{
    return d_load_lines;
}


QAction *MenuBar::save_own_lines()
{
    return d_save_own_lines;
}


QAction *MenuBar::save_all_lines()
{
    return d_save_all_lines;
}