#ifndef CONTROL_MAPMANAGER_H
#define CONTROL_MAPMANAGER_H

#include <QJsonObject>
#include <QMap>
#include <QString>

#include "../model/griditemgroup.h"

class MapManager : public QObject
{
    Q_OBJECT

    QString d_selection;
    QMap<QString, GridItemGroup> d_grid_groups;

    public:
        explicit MapManager(QObject *parent = nullptr);
        ~MapManager();

        // getters
        QMap<QString, GridItemGroup> const &grid_groups() const;
        
        // utility
        void add_group(QString const &name);
        void set_selection(QString const &name);
        
        QString const &selected_group_name() const;
        GridItemGroup &selected_group();
        GridItemGroup &find_group(QString const &name);

        // slots
        void on_grid_item_added(QJsonObject const &obj);
        void on_group_visibility(QString const &group, VisibilityMode mode);

    signals:
        void update_grid();
        void selection_changed();
        void pixmap_required(QString const &key);


};

#endif