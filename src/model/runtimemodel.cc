#include "runtimemodel.h"

////////////////////
//  Constructors  //
////////////////////

RuntimeModel::RuntimeModel()
{
    load_spells();
}


RuntimeModel::~RuntimeModel()
{

}


////////////////////
//    Getters     //
////////////////////

PixmapCache &RuntimeModel::pixmap_cache() noexcept
{
    return d_pixmap_cache;
}


QMap<QString, Spell> &RuntimeModel::spells_cache() noexcept
{
    return d_spells_cache;
}


////////////////////
//    Loading     //
////////////////////

void RuntimeModel::load_spells()
{
    QJsonDocument root = load_json_file(":data/spells.json");
    QJsonArray sources = root["sources"].toArray();

    for (QJsonValue source : sources)
    {
        QString source_name = source["name"].toString();
        QJsonArray spells = source["spells"].toArray();
        for (QJsonValue spell : spells)
        {
            Spell parsed{spell.toObject(), source_name};
            d_spells_cache.insert(parsed.name(), parsed);
        }
    }
}