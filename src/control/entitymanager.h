#ifndef CONTORL_ENTITYMANAGER_H
#define CONTORL_ENTITYMANAGER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

#include "../model/entity.h"

class EntityManager : public QObject
{
    Q_OBJECT

    QMap<QString, Entity> d_entities;

    public:
        explicit EntityManager(QObject *parent = nullptr);
        ~EntityManager();

        // utility
        void clear();
        QMap<QString, Entity> const &entities() const;

    public slots:
        void on_entity_added(QJsonObject const &obj);
        void on_entities_removed(QJsonObject const &obj);
        void on_entities_cleared();
        void on_entities_moved(QJsonObject const &obj);
        void on_entities_synchronized(QJsonObject const &obj);

    signals:
        void update_grid();
        void pixmap_required(QString const &key);
};

#endif