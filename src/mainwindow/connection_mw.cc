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
    if (d_server != nullptr || d_client != nullptr)
    {
        debug_output("H: Already connected...");
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

    connect_host_networking();
    d_server->start_listening(4144);
}


void MainWindow::on_client_pressed([[maybe_unused]] bool triggered)
{
    if (d_server != nullptr || d_client != nullptr)
    {
        debug_output("C: Already connected...");
        return;
    }

    ConnectDialog dialog{this};
    if (dialog.exec() == QDialog::Rejected)
        return;

    ConnectDialogInfo info = dialog.get_entries();
    if (info.character_name == "")
        return;

    d_client = new ClientConnection;
    QObject::connect
    (
        d_client,
        &ClientConnection::connection_status_update,
        d_status_bar,
        &StatusBar::update_connection_status
    );

    connect_client_networking();
    d_client->connect(info.hostname, info.port);

    // send first hello!
    QJsonObject document;
    document["type"] = "HANDSHAKE";
    document["character_name"] = info.character_name;
    QJsonObject avatar;
    avatar["filename"] = info.pixmap_path;
    avatar["data"] = read_file_conditionally_b64(info.pixmap_path);
    document["avatar"] = avatar;

    QJsonDocument root{document};
    QString blob = root.toJson();
    d_client->send(blob);
}