#include "mainwindow.h"

void MainWindow::connect_host_networking()
{
    QObject::connect
    (
        d_server,
        &HostConnection::display_update_message,
        this,
        &MainWindow::on_display_update
    );
}


void MainWindow::connect_client_networking()
{
    QObject::connect
    (
        d_client,
        &ClientConnection::display_update_message,
        this,
        &MainWindow::on_display_update
    );
}


void MainWindow::on_display_update(QJsonDocument const &doc)
{
    QByteArray data = QByteArray::fromBase64(doc.object()["data"].toString().toLocal8Bit());
    
    QPixmap image;
    image.loadFromData(data);

    d_central_widget->display_widget()->set_pixmap(std::move(image));
}