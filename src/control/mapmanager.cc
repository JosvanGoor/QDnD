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
    if (auto it = d_grid_groups.find(name); it != d_grid_groups.end())
        return it.value();
    return d_grid_groups["<default>"];
}


////////////////////
//     Slots      //
////////////////////

void MapManager::on_grid_item_added(QJsonObject const &obj)
{
    GridItem item;
    item.pixmap_code = obj["pixmap"].toString();
    item.position = QPoint{obj["x"].toInt(), obj["y"].toInt()};
    item.rotation = obj["rotation"].toInt();
    item.scale = static_cast<GridScale>(obj["scale"].toInt());
    item.visibility = static_cast<VisibilityMode>(obj["visibility"].toInt());

    QString group = obj["group"].toString();
    if (auto it = d_grid_groups.find(group); it != d_grid_groups.end())
        it.value().items().push_back(item);
    else
    {
        d_grid_groups[group] = GridItemGroup{group};
        d_grid_groups[group].items().push_back(item);
    }

    emit pixmap_required(item.pixmap_code);
    emit update_grid();
}


void MapManager::on_group_visibility(QString const &group, VisibilityMode mode)
{
    if (auto it = d_grid_groups.find(group); it != d_grid_groups.end())
        it.value().set_visibility(mode);
    else
        d_grid_groups[group] = GridItemGroup{group, mode};
}