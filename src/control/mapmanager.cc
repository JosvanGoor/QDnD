#include "mapmanager.h"

////////////////////
//  Constructor   //
////////////////////

MapManager::MapManager(QObject *parent)
:   QObject(parent)
{
    d_selection = "<default>";
    d_grid_groups["<default>"] = GridItemGroup{"<default>", VisibilityMode::VISIBLE};
}


MapManager::~MapManager()
{

}


////////////////////
//    Getters     //
////////////////////

QMap<QString, GridItemGroup> const &MapManager::grid_groups() const
{
    return d_grid_groups;
}


////////////////////
//    Utility     //
////////////////////

void MapManager::add_group(QString const &name)
{
    if (auto it = d_grid_groups.find("name"); it != d_grid_groups.end())
        return;
    d_grid_groups[name] = GridItemGroup{name};
}


void MapManager::set_selection(QString const &name)
{
    d_selection = name;
    emit selection_changed();
}


QString const &MapManager::selected_group_name() const
{
    return d_selection;
}


GridItemGroup &MapManager::selected_group()
{
    if (d_selection == "")
        return d_grid_groups["<default>"];
    else return find_group(d_selection);
}


GridItemGroup &MapManager::find_group(QString const &name)
{
    return d_grid_groups[name];
}