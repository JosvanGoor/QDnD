#include "griditemgroup.h"

////////////////////
//  Constructor   //
////////////////////

GridItemGroup::GridItemGroup()
:   d_name("__ERROR__"),
    d_visibility(VisibilityMode::HIDDEN),
    d_items(),
    d_filename_dict()
{ }


GridItemGroup::GridItemGroup(QString const &name, VisibilityMode mode)
:   d_name(name),
    d_visibility(mode),
    d_items(),
    d_filename_dict()
{ }


////////////////////
//    Getters     //
////////////////////

QString const &GridItemGroup::name() const
{
    return d_name;
}


VisibilityMode GridItemGroup::visibility_mode() const
{
    return d_visibility;
}


QVector<GridItem> &GridItemGroup::items()
{
    return d_items;
}


QVector<GridItem> const &GridItemGroup::items() const
{
    return d_items;
}


////////////////////
//   Serialize    //
////////////////////

void GridItemGroup::clear()
{
    d_items.clear();
    d_visibility = VisibilityMode::HIDDEN;
}


void GridItemGroup::set_visibility(VisibilityMode mode)
{
    d_visibility = mode;
}


////////////////////
//   Serialize    //
////////////////////

QJsonObject GridItemGroup::serialize(bool include_filenames) const noexcept
{
    QJsonArray items;
    for (GridItem const &item : d_items)
        items.push_back(serialize_item(item));
 
    QJsonObject obj;
    obj["name"] = d_name;
    obj["visibility"] = as_int(d_visibility);
    obj["items"] = items;

    if (include_filenames)
        obj["filenames"] = serialize_filenames();

    return obj;
}


QJsonObject GridItemGroup::serialize_filenames() const
{
    QJsonObject obj;

    for (auto it = d_filename_dict.begin(); it != d_filename_dict.end(); ++it)
        obj[it.key()] = it.value();

    return obj;
}


QJsonObject GridItemGroup::serialize_item(GridItem const &item) const noexcept
{
    QJsonObject obj;
    obj["pixmap_code"] = item.pixmap_code;
    obj["x"] = item.position.x();
    obj["y"] = item.position.y();
    obj["rotation"] = item.rotation;
    obj["scale"] = as_int(item.scale);
    obj["visibility"] = as_int(item.visibility);
    
    return obj;
}


////////////////////
//  Deserialize   //
////////////////////

void GridItemGroup::from_file(QString const &filename)
{
    clear();
    QJsonDocument root = load_json_file(filename);
    deserialize(root.object());   
}


void GridItemGroup::deserialize(QJsonObject const &obj)
{
    d_name = obj["name"].toString();
    d_visibility = static_cast<VisibilityMode>(obj["visibility"].toInt());

    QJsonArray items = obj["items"].toArray();

    for (auto objval : items)
        deserialize_item(objval.toObject());
}


void GridItemGroup::deserialize_item(QJsonObject const &obj)
{
    d_items.push_back(GridItem{});
    d_items.back().pixmap_code = obj["pixmap_code"].toString();
    d_items.back().position = {obj["x"].toInt(), obj["y"].toInt()};
    d_items.back().rotation = obj["rotation"].toInt();
    d_items.back().scale = static_cast<GridScale>(obj["scale"].toInt());
    d_items.back().visibility = static_cast<VisibilityMode>(obj["visibility"].toInt());
}