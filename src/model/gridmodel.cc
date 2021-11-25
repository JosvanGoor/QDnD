#include "gridmodel.h"

////////////////////
//  Constructors  //
////////////////////

GridModel::GridModel()
:   d_name("Default"),
    d_foreground_color(Qt::black),
    d_background_color(Qt::white),
    d_items()
{ }


GridModel::~GridModel()
{
    
}


////////////////////
//    Setters     //
////////////////////

void GridModel::set_name(QString const &name)
{
    d_name = name;
}


void GridModel::set_foreground_color(QColor const &color)
{
    d_foreground_color = color;
}


void GridModel::set_background_color(QColor const &color)
{
    d_background_color = color;
}


////////////////////
//    Setters     //
////////////////////

QString const &GridModel::name() const noexcept
{
    return d_name;
}


QColor GridModel::foreground_color() const noexcept
{
    return d_foreground_color;
}


QColor GridModel::background_color() const noexcept
{
    return d_background_color;
}


GridItemGroup &GridModel::items(QString const &name) noexcept
{
    return d_items[name];
}


////////////////////
//  Manipulation  //
////////////////////

void GridModel::add_line(QString const &user, QString const &name, GridLine const &line)
{
    d_lines[user][name] = line;
}


void GridModel::remove_line(QString const &user, QString const &name)
{
    auto uit = d_lines.find(user);
    if (uit == d_lines.end())
        return;

    auto lit = uit.value().find(name);
    if (lit == uit.value().end())
        return;

    uit.value().erase(lit);
}


void GridModel::remove_user_lines(QString const &user)
{
    if (auto it = d_lines.find(user); it != d_lines.end())
        d_lines.erase(it);
}