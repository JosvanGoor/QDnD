#include "mainwindow.h"

void MainWindow::on_token_added(QJsonDocument const &doc)
{
    QString name = doc.object()["name"].toString();
    QByteArray raw_avatar = QByteArray::fromBase64(doc.object()["data"].toString().toLocal8Bit());
    QPixmap image;
    image.loadFromData(raw_avatar);

    d_central_widget->grid_widget()->add_avatar(name, image);
}


void MainWindow::on_token_removed(QString const &name)
{
    debug_output("Deleting " + name);
    d_central_widget->grid_widget()->delete_avatar(name);
}


void MainWindow::on_monster_removed(QString const &name)
{
    QJsonObject obj;
    obj["type"] = "MONSTER_REMOVED";
    obj["name"] = name;
    d_server->dispatch(QJsonDocument{obj});

    d_central_widget->grid_widget()->delete_avatar(name);
}


void MainWindow::on_monster_added(MonsterInfo const &info)
{
    QByteArray encoded_data = info.raw_pixmap.toBase64();

    QJsonObject obj;
    obj["type"] = "MONSTER_ADDED";
    obj["name"] = info.name;
    obj["data"] = QString{encoded_data};
    d_server->dispatch(QJsonDocument{obj});

    debug_output("Monster pixmap size: " + QString::number(info.raw_pixmap.size()));

    QPixmap avatar;
    avatar.loadFromData(info.raw_pixmap);
    d_central_widget->grid_widget()->add_avatar(info.name, avatar);
}


void MainWindow::on_monster_selected(QString const &name)
{
    debug_output("Selected Monster: " + name);
    d_central_widget->grid_widget()->set_controlled_avatar(name);
}