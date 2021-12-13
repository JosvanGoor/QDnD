#ifndef MODEL_ENTITY_H
#define MODEL_ENTITY_H

#include <QPoint>
#include <QString>

#include "../utility/enums.h"

class Entity
{
    QString d_avatar;  
    QPoint d_position;
    int d_rotation;
    GridScale d_scale;

    public:
        Entity();
        Entity(QString const &avatar, QPoint const &position);

        // Set/Get
        QString const &avatar() const;
        QPoint const &position() const;
        int rotation() const;
        GridScale scale() const;

        void set_avatar(QString const &avatar);
        void set_postion(QPoint const &position);
        void set_rotation(int rotation);
        void set_scale(GridScale scale);
};

#endif