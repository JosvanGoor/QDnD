#ifndef RUNTIMEMODEL_H
#define RUNTIMEMODEL_H

#include <QMap>

#include "spell.h"
#include "../utility/loading.h"

struct RuntimeModel
{
    QMap<QString, Spell> d_spells_cache;

    public:
        RuntimeModel();
        ~RuntimeModel();

    
    private:
        void load_spells();
};

#endif