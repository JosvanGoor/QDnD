#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
:   QMainWindow(parent)
{
    // null out connections
    d_server = nullptr;
    d_client = nullptr;

    d_menu_bar = new MenuBar;
    setMenuBar(d_menu_bar);

    d_central_widget = new CentralWidget;
    setCentralWidget(d_central_widget);

    d_status_bar = new StatusBar;
    setStatusBar(d_status_bar);

    QObject::connect
    (
        d_central_widget->display_control_widget()->select_button(),
        &QPushButton::pressed,
        this,
        &MainWindow::on_select_display
    );

    QObject::connect
    (
        this,
        &MainWindow::debug_output,
        d_central_widget->text_widget(),
        &TextWidget::add_text
    );

    connect_connection_buttons();

    resize(1600, 900);
}


MainWindow::~MainWindow()
{

}