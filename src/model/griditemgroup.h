#ifndef MODEL_GRIDITEMGROUP_H
#define MODEL_GRIDITEMGROUP_H

#include <QString>
#include <QVector>
#include <QJsonArray>
#include <QJsonObject>

#include "../utility/enums.h"
#include "../utility/loading.h"

struct GridItem
{
    QString name;
    QString pixmap_file;    // filename for host
    QString pixmap_code;    // code for net use
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
    // QVector<GridItemGroup> d_subgroups; // lets keep it simple

    public:
        GridItemGroup(QString const &name = "group");

        // utility
        void clear();

        // serialization
        QJsonObject serialize() const noexcept;
        QJsonObject serialize_item(GridItem const &item) const noexcept;

        // deserialization
        void from_file(QString const &filename);
        void deserialize(QJsonObject const &obj);
        void deserialize_item(QJsonObject const &obj);
};

#endif