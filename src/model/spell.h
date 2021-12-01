#ifndef MODEL_SPELL_H
#define MODEL_SPELL_H

#include <QJsonArray>
#include <QJsonObject>
#include <QString>

#include "../utility/htmlformatting.h"

class Spell
{
    QString d_name;
    QString d_source;
    int d_level;
    bool d_ritual;
    QString d_range;
    QString d_casting_time;
    QString d_duration;
    QString d_components;
    QString d_school;
    QString d_classes;
    QString d_description;

    public:
        Spell();
        Spell(QJsonObject const &object, QString const &source = "Unknown");

        QString name() const noexcept;
        QString format() const noexcept;

    private:
        QString parse_classes(QJsonArray const &classes) noexcept;
        QString parse_components(QJsonObject const &object) noexcept;
        QString parse_description(QJsonObject const &object) noexcept;
};

#endif