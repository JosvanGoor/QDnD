#include "menubar.h"

MenuBar::MenuBar(QWidget *parent)
:   QMenuBar(parent)
{
    d_file = new QMenu{"File"};
    d_new = new QAction{"New Scenario"};
    d_open = new QAction{"Open Scenario"};
    d_save = new QAction{"Save..."};
    d_save_as = new QAction{"Save As..."};
    d_quit = new QAction{"Quit"};

    d_debug = new QAction{"Debug Output"};
    d_debug->setCheckable(true);
    d_debug->setChecked(true);

    d_file->addAction(d_new);
    d_file->addAction(d_open);
    d_file->addAction(d_save);
    d_file->addAction(d_save_as);
    d_file->addAction(d_quit);
    d_file->addSeparator();
    d_file->addAction(d_debug);

    d_connection = new QMenu{"Connection"};
    d_connect = new QAction{"Connect..."};
    d_host = new QAction{"Host"};
    d_disconnect = new QAction{"Disconnect..."};

    d_connection->addAction(d_host);
    d_connection->addAction(d_connect);
    d_connection->addAction(d_disconnect);

    addMenu(d_file);
    addMenu(d_connection);
    // addAction(d_debug);
}


MenuBar::~MenuBar()
{

}


bool MenuBar::output_debug_info() const noexcept
{
    return d_debug->isChecked();
}