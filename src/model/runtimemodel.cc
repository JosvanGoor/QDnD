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