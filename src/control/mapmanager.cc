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

void MapManager::clear_map()
{
    d_grid_groups.clear();
}


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


QJsonArray MapManager::jsonify_map(bool filenames)
{
    QJsonArray arr;
    for (auto &group : d_grid_groups)
        arr.push_back(group.serialize(filenames));
    return arr;
}


void MapManager::clean_from_json(QJsonObject const &obj)
{
    d_grid_groups.clear();
    QJsonArray groups = obj["groups"].toArray();

    for (auto groupval : groups)
    {
        QJsonObject group = groupval.toObject();

        QString name = group["name"].toString();
        VisibilityMode mode = static_cast<VisibilityMode>(group["visibility"].toInt());
        GridItemGroup &current = (d_grid_groups[name] = GridItemGroup{name, mode});

        if (auto it = group.find("filenames"); it != group.end())
        {
            QJsonObject filenames = it.value().toObject();
            for (auto it = filenames.begin(); it != filenames.end(); ++it)
            {
                emit preload_pixmap(it.value().toString(), it.key());
                current.list_filename(it.key(), it.value().toString());
            }
        }

        QJsonArray items = group["items"].toArray();
        for (auto itemval : items)
            current.deserialize_item(itemval.toObject());
    }
}


////////////////////
//     Slots      //
////////////////////

void MapManager::on_synchronize_grid_group(QJsonObject const &obj)
{
    GridItemGroup group;
    group.deserialize(obj["group"].toObject());
    d_grid_groups[group.name()] = group;

    for (auto &item : group.items())
        emit pixmap_required(item.pixmap_code);
    emit update_grid();
}


void MapManager::on_grid_item_added(QJsonObject const &obj)
{
    QString group = obj["group"].toString();
    if (auto it = d_grid_groups.find(group); it != d_grid_groups.end())
        it.value().deserialize_item(obj);
    else
    {
        (d_grid_groups[group] = GridItemGroup{group}).deserialize_item(obj);
    }

    emit pixmap_required(obj["pixmap_code"].toString());
    emit update_grid();
}


void MapManager::on_group_visibility(QString const &group, VisibilityMode mode)
{
    if (auto it = d_grid_groups.find(group); it != d_grid_groups.end())
        it.value().set_visibility(mode);
    else
        d_grid_groups[group] = GridItemGroup{group, mode};
    emit update_grid();
}