#include "gridmodel.h"

////////////////////
//  Constructors  //
////////////////////

GridModel::GridModel()
:   d_items("Root"),
    d_foreground_color(Qt::black),
    d_background_color(Qt::white)
{ }


GridModel::~GridModel()
{
    
}


////////////////////
//    Setters     //
////////////////////

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

GridItemGroup &GridModel::items() noexcept
{
    return d_items;
}


QColor GridModel::foreground_color() const noexcept
{
    return d_foreground_color;
}


QColor GridModel::background_color() const noexcept
{
    return d_background_color;
}