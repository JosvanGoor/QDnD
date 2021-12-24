#include "entitymanager.h"

////////////////////
//  Constructor   //
////////////////////

EntityManager::EntityManager(QObject *parent)
:   QObject(parent)
{ }


EntityManager::~EntityManager()
{ }


////////////////////
//    Utility     //
////////////////////

void EntityManager::clear()
{
    d_entities.clear();
    emit update_grid();
}


QMap<QString, Entity> const &EntityManager::entities() const
{
    return d_entities;
}


////////////////////
//     Slots      //
////////////////////

void EntityManager::on_entity_added(QJsonObject const &obj)
{
    QString name = obj["name"].toString();
    QString avatar = obj["avatar"].toString();
    QPoint pos{obj["x"].toInt(), obj["y"].toInt()};
    GridScale scale = static_cast<GridScale>(obj["scale"].toInt());

    d_entities[name] = Entity{avatar, pos, scale};
    emit pixmap_required(avatar);
    emit update_grid();
}


void EntityManager::on_entities_removed(QJsonObject const &obj)
{
    QJsonArray entities = obj["entities"].toArray();

    for (auto entity : entities)
    {
        if (auto it = d_entities.find(entity.toString()); it != d_entities.end())
            d_entities.erase(it);
    }

    emit update_grid();
}


void EntityManager::on_entities_cleared()
{
    d_entities.clear();
    emit update_grid();
}


void EntityManager::on_entities_moved(QJsonObject const &obj)
{
    QPoint pos{obj["x"].toInt(), obj["y"].toInt()};
    QJsonArray entities = obj["entities"].toArray();

    for (auto entity : entities)
    {
        if (auto it = d_entities.find(entity.toString()); it != d_entities.end())
            it.value().set_postion(pos);
    }

    emit update_grid();
}


void EntityManager::on_entities_rotated(QJsonObject const &obj)
{
    QJsonArray entities = obj["entities"].toArray();
    int angle = obj["angle"].toInt();

    for (auto entity : entities)
    {
        if (auto it = d_entities.find(entity.toString()); it != d_entities.end())
            it.value().set_rotation(it.value().rotation() + angle);
    }

    emit update_grid();
}


void EntityManager::on_entities_synchronized(QJsonObject const &obj)
{
    QJsonArray entities = obj["entities"].toArray();

    for (auto entity : entities)
    {
        QJsonObject obj = entity.toObject();
        QString name = obj["name"].toString();
        QString avatar = obj["avatar"].toString();
        GridScale scale = static_cast<GridScale>(obj["scale"].toInt());
        QPoint pos{obj["x"].toInt(), obj["y"].toInt()};
        int rotation = obj["rotation"].toInt();

        // this is so ugly lol
        d_entities[name] = Entity{avatar, pos, scale, rotation};
        emit pixmap_required(avatar);
    }

    emit update_grid();
}