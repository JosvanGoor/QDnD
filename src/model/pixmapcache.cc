#include "pixmapcache.h"

////////////////////
//  Constructors  //
////////////////////

PixmapCache::PixmapCache()
{
    d_missing_texture.load(":/data/missing_texture.jpg");
}


PixmapCache::~PixmapCache()
{

}


////////////////////
//     Public     //
////////////////////

bool PixmapCache::has_pixmap(QString const &name) const noexcept
{
    auto it = d_pixmaps.find(name);
    return it != d_pixmaps.end();
}


bool PixmapCache::load_pixmap(QString const &name, QByteArray const &b64_data) noexcept
{
    QPixmap map = load_from_b64(b64_data);
    if (!map.isNull())
    {
        d_pixmaps[name] = map;
        return true;
    }

    return false;
}


QPixmap const &PixmapCache::get_pixmap(QString const &name) const noexcept
{
    if (auto it = d_pixmaps.find(name); it != d_pixmaps.end())
        return it.value();
    return d_missing_texture;
}


TransferableImage PixmapCache::load_from_file(QString const &filename) noexcept
{
    QFile file{filename};
    if (!file.exists())
        return {};

    TransferableImage rval;
    QByteArray data = file.readAll();

    QPixmap pixmap;
    if (!pixmap.loadFromData(data))
        return {};

    rval.b64_data = data.toBase64();
    rval.name = QCryptographicHash::hash(rval.b64_data, QCryptographicHash::Sha1);
    d_pixmaps[rval.name] = pixmap;
    return rval;
}


////////////////////
//    Private     //
////////////////////

QPixmap PixmapCache::load_from_b64(QByteArray const &b64_data) const noexcept
{
    QPixmap rval;
    QByteArray raw_data = QByteArray::fromBase64(b64_data);
    rval.loadFromData(raw_data);

    return rval;
}