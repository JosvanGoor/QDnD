#include "startupwindow.h"

StartupWindow::StartupWindow(QWidget *parent)
:   QMainWindow(parent)
{
    // setup central widget
    d_central_widget = new QWidget;
    this->setCentralWidget(d_central_widget);
    d_central_widget->setLayout(new QVBoxLayout);

    // setup new session widget
    d_new_session_widget = new QGroupBox;
    d_new_session_widget->setLayout(new QVBoxLayout);
    d_new_session_button = new QPushButton("New Scenario");
    d_new_session_widget->layout()->addWidget(d_new_session_button);

    // load session widget
    d_load_session_widget = new QGroupBox;
    d_load_session_widget->setLayout(new QVBoxLayout);
    d_load_session_button = new QPushButton("Load Scenario");
    QWidget *filename_widget = new QWidget;
    filename_widget->setLayout(new QFormLayout);
    d_load_session_filename = new QLineEdit;
    d_load_session_portnr = new QLineEdit;
    reinterpret_cast<QFormLayout*>(filename_widget->layout())->addRow("File: ", d_load_session_filename);
    reinterpret_cast<QFormLayout*>(filename_widget->layout())->addRow("Port: ", d_load_session_portnr);
    d_load_session_widget->layout()->addWidget(d_load_session_button);
    d_load_session_widget->layout()->addWidget(filename_widget);
    
    // join session widget
    d_join_session_widget = new QGroupBox;
    d_join_session_widget->setLayout(new QVBoxLayout);
    d_join_session_button = new QPushButton("Join Scenario");
    QWidget *join_widget = new QWidget;
    QFormLayout *formlayout = new QFormLayout;
    join_widget->setLayout(formlayout);
    d_join_session_address = new QLineEdit;
    d_join_session_name = new QLineEdit;
    formlayout->addRow("Host: ", d_join_session_address);
    formlayout->addRow("Name: ", d_join_session_name);
    d_join_session_widget->layout()->addWidget(d_join_session_button);
    d_join_session_widget->layout()->addWidget(join_widget);

    // combine parts
    d_central_widget->layout()->addWidget(d_new_session_widget);
    d_central_widget->layout()->addWidget(d_load_session_widget);
    d_central_widget->layout()->addWidget(d_join_session_widget);

    // show and stuff
    adjustSize();
}


StartupWindow::~StartupWindow()
{

}