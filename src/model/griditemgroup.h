#ifndef MODEL_GRIDITEMGROUP_H
#define MODEL_GRIDITEMGROUP_H

#include <QString>
#include <QVector>

#include "../utility/enums.h"

struct GridItem
{
    QString name;
    int x_pos                   = 0;
    int y_pos                   = 0;
    int rotation                = 0;
    GridScale scale             = GridScale::MEDIUM;
    VisibilityMode visibility   = VisibilityMode::PARENT;
};


struct GridItemGroup
{
    QString d_name;
    VisibilityMode d_visibility;
    QVector<GridItem> d_items;
    QVector<GridItemGroup> d_subgroups;

    public:
        GridItemGroup(QString const &name);
};

#endif