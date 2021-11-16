#include "mainwindow.h"

void MainWindow::line_removed(QString const &name)
{
    QJsonObject obj;
    obj["type"] = "LINE_REMOVED";
    obj["name"] = name;

    debug_output("Dispatching line_removed");

    if (d_server)
        d_server->dispatch(QJsonDocument{obj});
    if (d_client)
        d_client->send(QJsonDocument{obj}.toJson());
}


void MainWindow::line_drawn(QVector<QLine> const &lines)
{
    QString name = d_line_prefix + " " + QString::number(d_linecounter++);
    QColor color;

    if (d_server)
        color = Qt::black;
    else if (d_client)
        color = Qt::red;
    else return;

    QJsonObject obj;
    obj["type"] = "NEW_LINE";
    obj["name"] = name;
    obj["r"] = color.red();
    obj["g"] = color.green();
    obj["b"] = color.blue();
    QJsonArray arr;
    
    for (QLine const &line : lines)
    {
        QJsonArray inner;
        inner.push_back(line.x1());
        inner.push_back(line.y1());
        inner.push_back(line.x2());
        inner.push_back(line.y2());
        arr.push_back(inner);
    }
    obj["line"] = arr;

    if (d_server)
    {
        d_server->dispatch(QJsonDocument{obj});
        d_central_widget->grid_widget()->add_line(name, color, lines);
    }
    if (d_client)
        d_client->send(QJsonDocument{obj}.toJson());
}


void MainWindow::move_avatar(QString const &name, QPoint const &pos)
{
    QJsonObject obj;
    obj["type"] = "AVATAR_MOVED";
    obj["name"] = name;
    obj["x"] = pos.x();
    obj["y"] = pos.y();

    if (d_server)
        d_server->dispatch(QJsonDocument(obj));
    if (d_client)
        d_client->send(QJsonDocument(obj).toJson());
}


void MainWindow::on_avatar_moved(QString const &name, QPoint const &pos)
{
    d_central_widget->grid_widget()->move_avatar(name, pos);
}