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

    d_entities[name] = Entity{avatar, pos};
    emit pixmap_required(avatar);
}


void EntityManager::on_entities_removed(QJsonObject const &obj)
{
    QJsonArray entities = obj["entities"].toArray();

    for (auto entity : entities)
    {
        if (auto it = d_entities.find(entity.toString()); it != d_entities.end())
            d_entities.erase(it);
    }
}


void EntityManager::on_entities_cleared()
{
    d_entities.clear();
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

        // this is so ugly lol
        (d_entities[name] = Entity{avatar, pos}).set_scale(scale);
        emit pixmap_required(avatar);
    }
}