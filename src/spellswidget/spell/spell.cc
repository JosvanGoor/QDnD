#include "spell.h"

Spell::Spell(QJsonObject const &object, QString const &source)
{
    d_source = source;
    d_name = object["name"].toString();
    d_level = object["level"].toInt();
    d_ritual = object["ritual"].toBool();
    d_range = object["range"].toString();
    d_casting_time = object["casting_time"].toString();
    d_duration = object["duration"].toString();
    d_components = string_components(object["components"].toObject());
    d_school = object["school"].toString();
    d_classes = string_classes(object["classes"].toArray());
    d_description = string_description(object["description"].toObject());

    this->setText(d_name);
}