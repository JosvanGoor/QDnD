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

    d_file->addAction(d_new);
    d_file->addAction(d_open);
    d_file->addAction(d_save);
    d_file->addAction(d_save_as);
    d_file->addAction(d_quit);

    addMenu(d_file);
}


MenuBar::~MenuBar()
{

}