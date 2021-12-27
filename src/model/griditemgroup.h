#ifndef MODEL_GRIDITEMGROUP_H
#define MODEL_GRIDITEMGROUP_H

#include <QPoint>
#include <QString>
#include <QVector>
#include <QJsonArray>
#include <QJsonObject>

#include "../utility/enums.h"
#include "../utility/loading.h"

struct GridItem
{
    QString pixmap_code;    // code for net use
    QPoint position             = {};
    int rotation                = 0;
    GridScale scale             = GridScale::MEDIUM;
    VisibilityMode visibility   = VisibilityMode::PARENT;
};


struct GridItemGroup
{
    QString d_name;
    VisibilityMode d_visibility;
    QVector<GridItem> d_items;
    QMap<QString, QString> d_filename_dict;

    public:
        GridItemGroup();
        GridItemGroup(QString const &name, VisibilityMode mode = VisibilityMode::HIDDEN);

        // getters
        QString const &name() const;
        VisibilityMode visibility_mode() const;
        QVector<GridItem> &items();
        QVector<GridItem> const &items() const;

        // utility
        void clear();
        void set_visibility(VisibilityMode mode);
        void list_filename(QString const &key, QString const &filename);

        // serialization
        QJsonObject serialize(bool include_filenames = true) const noexcept;
        QJsonObject serialize_filenames() const;
        QJsonObject serialize_item(GridItem const &item) const noexcept;

        // deserialization
        void from_file(QString const &filename);
        void deserialize(QJsonObject const &obj);
        void deserialize_item(QJsonObject const &obj);
};

#endif