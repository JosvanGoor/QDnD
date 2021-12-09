#include "entity.h"

////////////////////
//  Constructor   //
////////////////////

Entity::Entity()
:   d_avatar(),
    d_position(),
    d_rotation(),
    d_scale()
{ }


Entity::Entity(QString const &avatar, QPoint const &position)
:   d_avatar(avatar),
    d_position(position),
    d_rotation(0),
    d_scale(GridScale::MEDIUM)
{ }


////////////////////
//    Set/Get     //
////////////////////

QString const &Entity::avatar() const
{
    return d_avatar;
}


QPoint const &Entity::position() const
{
    return d_position;
}


int Entity::rotation() const
{
    return d_rotation;
}


GridScale Entity::scale() const
{
    return d_scale;
}


void Entity::set_avatar(QString const &avatar)
{
    d_avatar = avatar;
}


void Entity::set_postion(QPoint const &position)
{
    d_position = position;
}


void Entity::set_rotation(int rotation)
{
    d_rotation = rotation;
}


void Entity::set_scale(GridScale scale)
{
    d_scale = scale;
}