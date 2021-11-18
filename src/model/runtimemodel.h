#ifndef RUNTIMEMODEL_H
#define RUNTIMEMODEL_H

#include <QMap>

#include "pixmapcache.h"
#include "spell.h"
#include "../utility/loading.h"

struct RuntimeModel
{
    PixmapCache d_pixmap_cache;
    QMap<QString, Spell> d_spells_cache;
    

    public:
        RuntimeModel();
        ~RuntimeModel();

        // getters
        PixmapCache &pixmap_cache() noexcept;
        QMap<QString, Spell> &spells_cache() noexcept;
    
    private:
        void load_spells();
};

#endif