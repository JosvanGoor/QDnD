#ifndef CONTROL_MAPMANAGER_H
#define CONTROL_MAPMANAGER_H

#include <QMap>
#include <QObject>
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

        GridItemGroup &selected_group();
        GridItemGroup &find_group(QString const &name);

    signals:
        void selection_changed();


};

#endif