#include "gridwidget.h"

void GridWidget::paint_avatars(QPainter *painter)
{
    for (auto &it : d_avatars)
    {
        painter->translate(QPoint{d_offset_x, d_offset_y});
        QRect rect{it.position.x(), it.position.y(), 64, 64};
        painter->drawPixmap(rect, it.avatar);
        painter->translate(QPoint{-d_offset_x, -d_offset_y});
    }
}


void GridWidget::add_avatar(QString const &name, QPixmap const &avatar)
{
    QPixmap scaled = avatar.scaled(64, 64);
    d_avatars[name] = {scaled, {0, 0}};
    update();
}


void GridWidget::move_avatar(QString const &name, QPoint const &pos)
{
    if (auto it = d_avatars.find(name); it != d_avatars.end())
        it.value().position = pos;
    update();
}


void GridWidget::delete_avatar(QString const &name)
{
    if (auto it = d_avatars.find(name); it != d_avatars.end())
        d_avatars.erase(it);
    if (name == d_controlled_avatar)
        d_controlled_avatar = "";
    update();
}


void GridWidget::set_controlled_avatar(QString const &name)
{
    d_controlled_avatar = name;
}


QString const &GridWidget::controlled_avatar()
{
    return d_controlled_avatar;
}