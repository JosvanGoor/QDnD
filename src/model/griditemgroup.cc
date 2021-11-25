#include "griditemgroup.h"

////////////////////
//  Constructor   //
////////////////////

GridItemGroup::GridItemGroup(QString const &name)
:   d_name(name),
    d_visibility(VisibilityMode::HIDDEN),
    d_items()
{ }


////////////////////
//   Serialize    //
////////////////////

QJsonObject GridItemGroup::serialize() const noexcept
{
    QJsonArray items;
    for (GridItem const &item : d_items)
        items.push_back(serialize_item(item));
 
    QJsonObject obj;
    obj["name"] = d_name;
    obj["visibility"] = as_int(d_visibility);
    obj["items"] = items;
    return obj;
}


QJsonObject GridItemGroup::serialize_item(GridItem const &item) const noexcept
{
    QJsonObject obj;
    obj["name"] = item.name;
    obj["pixmap_file"] = item.pixmap_file;
    obj["pixmap_code"] = item.pixmap_code;
    obj["x_pos"] = item.x_pos;
    obj["y_pos"] = item.y_pos;
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
    d_items.back().name = obj["name"].toString();
    d_items.back().pixmap_file = obj["pixmap_file"].toString();
    d_items.back().pixmap_code = obj["pixmap_code"].toString();
    d_items.back().x_pos = obj["x_pos"].toInt();
    d_items.back().y_pos = obj["y_pos"].toInt();
    d_items.back().rotation = obj["rotation"].toInt();
    d_items.back().scale = static_cast<GridScale>(obj["scale"].toInt());
    d_items.back().visibility = static_cast<VisibilityMode>(obj["visibility"].toInt());
}