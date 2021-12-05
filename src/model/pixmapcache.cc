#include "pixmapcache.h"

#include <iostream> // TODO: remove

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

void PixmapCache::clear()
{
    d_pixmaps.clear();
}


bool PixmapCache::has_pixmap(QString const &name) const noexcept
{
    auto it = d_pixmaps.find(name);
    return it != d_pixmaps.end();
}


void PixmapCache::put_pixmap(QString const &name, QPixmap const &pixmap)
{
    d_pixmaps[name] = pixmap;
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


QString PixmapCache::load_from_memory(QByteArray const &b64_avatar) noexcept
{
    QPixmap pixmap;
    pixmap.loadFromData(QByteArray::fromBase64(b64_avatar));

    if (pixmap.isNull())
        return "";

    QString name = QCryptographicHash::hash(b64_avatar, QCryptographicHash::Sha1).toHex();
    d_pixmaps[name] = pixmap;
    return name;
}


TransferableImage PixmapCache::load_from_file(QString const &filename) noexcept
{
    QFile file{filename};
    if (!file.exists())
        return {};

    TransferableImage rval;
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    
    QPixmap pixmap;
    if (!pixmap.loadFromData(data))
        return {};

    rval.b64_data = data.toBase64();
    rval.name = QCryptographicHash::hash(rval.b64_data, QCryptographicHash::Sha1).toHex();
    d_pixmaps[rval.name] = pixmap;
    return rval;
}


TransferableImage PixmapCache::prepare_for_transfer(QString const &name) noexcept
{
    TransferableImage rval;
    auto it = d_pixmaps.find(name);
    if (it == d_pixmaps.end())
        return rval;
    
    QBuffer buffer{&rval.b64_data};
    buffer.open(QIODevice::WriteOnly);
    it.value().save(&buffer, "PNG");
    rval.name = name;
    rval.b64_data = rval.b64_data.toBase64();
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
