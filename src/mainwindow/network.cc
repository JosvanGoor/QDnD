#include "mainwindow.h"

void MainWindow::connect_host_networking()
{
    QObject::connect(d_server, &HostConnection::display_update_message, this, &MainWindow::on_display_update);
    QObject::connect(d_server, &HostConnection::new_connection, this, &MainWindow::on_new_connection);
    QObject::connect(d_server, &HostConnection::user_disconnected, this, &MainWindow::on_disconnect);
    QObject::connect(d_server, &HostConnection::avatar_move_message, this, &MainWindow::on_avatar_moved);
    QObject::connect(d_server, &HostConnection::line_received, this, &MainWindow::on_incoming_line);
    QObject::connect(d_server, &HostConnection::line_removed, this, &MainWindow::on_line_removed);
}


void MainWindow::connect_client_networking()
{
    QObject::connect(d_client, &ClientConnection::display_update_message, this, &MainWindow::on_display_update);
    QObject::connect(d_client, &ClientConnection::new_connection, this, &MainWindow::on_new_connection);
    QObject::connect(d_client, &ClientConnection::user_disconnected, this, &MainWindow::on_disconnect);
    QObject::connect(d_client, &ClientConnection::avatar_move_message, this, &MainWindow::on_avatar_moved);
    QObject::connect(d_client, &ClientConnection::line_received, this, &MainWindow::on_incoming_line);
    QObject::connect(d_client, &ClientConnection::line_removed, this, &MainWindow::on_line_removed);
}


void MainWindow::on_display_update(QJsonDocument const &doc)
{
    QByteArray data = QByteArray::fromBase64(doc.object()["data"].toString().toLocal8Bit());
    
    QPixmap image;
    image.loadFromData(data);

    d_central_widget->display_widget()->set_pixmap(std::move(image));
}


void MainWindow::on_new_connection(QJsonDocument const &doc)
{
    QString name = doc.object()["name"].toString();
    QByteArray raw_avatar = QByteArray::fromBase64(doc.object()["data"].toString().toLocal8Bit());
    QPixmap image;
    image.loadFromData(raw_avatar);

    d_central_widget->grid_widget()->add_avatar(name, image);
    d_central_widget->user_widget()->add_user(name, image);
}


void MainWindow::on_disconnect(QString const &name)
{
    d_central_widget->grid_widget()->delete_avatar(name);
    d_central_widget->user_widget()->remove_user(name);
}


void MainWindow::on_incoming_line(QJsonDocument const &doc)
{
    QString name = doc["name"].toString();
    QJsonArray const &line_arr = doc["line"].toArray();

    int r = doc["r"].toInt();
    int g = doc["g"].toInt();
    int b = doc["b"].toInt();
    QColor color{r, g, b};

    QVector<QLine> line;
    for (auto const &bit : line_arr)
    {
        int x1 = bit.toArray()[0].toInt();
        int y1 = bit.toArray()[1].toInt();
        int x2 = bit.toArray()[2].toInt();
        int y2 = bit.toArray()[3].toInt();
        line.push_back(QLine{x1, y1, x2, y2});
    }

    d_central_widget->grid_widget()->add_line(name, color, line);
}


void MainWindow::on_line_removed(QString const &name)
{
    debug_output("Deleting line " + name);
    d_central_widget->grid_widget()->silent_remove_line(name);
}