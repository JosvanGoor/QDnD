#include "mainwindow.h"

void MainWindow::connect_connection_buttons()
{
    QObject::connect
    (
        d_menu_bar->host_button(),
        &QAction::triggered,
        this,
        &MainWindow::on_host_pressed
    );

    QObject::connect
    (
        d_menu_bar->client_button(),
        &QAction::triggered,
        this,
        &MainWindow::on_client_pressed
    );
}


void MainWindow::on_host_pressed([[maybe_unused]] bool triggered)
{
    std::cout << "on_host_pressed\n" << std::flush;

    if (d_server != nullptr || d_client != nullptr)
    {
        debug_output("H: Already connected...\n");
        return;
    }

    d_server = new HostConnection;
    
    QObject::connect
    (
        d_server,
        &HostConnection::connection_status_update,
        d_status_bar,
        &StatusBar::update_connection_status
    );

    QObject::connect
    (
        d_server,
        &HostConnection::debug_message,
        d_central_widget->text_widget(),
        &TextWidget::add_text
    );

    d_server->start_listening(4144);
}


void MainWindow::on_client_pressed([[maybe_unused]] bool triggered)
{
    std::cout << "on_client_pressed\n" << std::flush;

    if (d_server != nullptr || d_client != nullptr)
    {
        debug_output("C: Already connected...\n");
        return;
    }

    d_client = new ClientConnection;

    QObject::connect
    (
        d_client,
        &ClientConnection::connection_status_update,
        d_status_bar,
        &StatusBar::update_connection_status
    );

    d_client->connect("localhost", 4144);
}