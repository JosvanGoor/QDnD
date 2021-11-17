#include "applicationcontrol.h"

////////////////////
//  Constructors  //
////////////////////

ApplicationControl::ApplicationControl(QObject *parent)
:   QObject(parent)
{
    d_main_window = new MainWindow;
    connect_to_mainwindow();

    d_runtime_model = new RuntimeModel;
    debug_output("Loaded " + QString::number(d_runtime_model->d_spells_cache.size()) + " spells.");

    load_settings();
    d_main_window->show();
}


ApplicationControl::~ApplicationControl()
{
    
}


////////////////////
//    Settings    //
////////////////////

void ApplicationControl::load_settings() noexcept
{
    debug_output("Started loading settings...");
    debug_output("Actually this function is empty :3");
}


////////////////////
//   Connecting   //
////////////////////

void ApplicationControl::connect_to_mainwindow()
{
    connect(this, &ApplicationControl::debug_output, d_main_window, &MainWindow::debug_message);
}