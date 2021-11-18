#ifndef MODEL_PIXMAPCACHE_H
#define MODEL_PIXMAPCACHE_H

#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QPixmap>

/*
    Pixmap files are recognised cross client by taking a Sha1 hash from their
    b64 encoded files in .jpg or .png encoding.

    The loading operations from this pixmapcache fail silently,
    When requesting a pixmap that doesn't exist a default 'missing pixmap' 
    pixmap is returned.

    Currently there is only caching in memory, since the interface might change
    a lot in following versions
*/

struct TransferableImage
{
    QString name;
    QByteArray b64_data;
};

class PixmapCache
{
    QPixmap d_missing_texture;
    QMap<QString, QPixmap> d_pixmaps;

    public:
        PixmapCache();
        ~PixmapCache();

        bool has_pixmap(QString const &name) const noexcept; // either in cache or memory
        bool load_pixmap(QString const &name, QByteArray const &b64_data) noexcept;
        QPixmap const &get_pixmap(QString const &name) const noexcept;

        TransferableImage load_from_file(QString const &filename) noexcept;

    private:
        QPixmap load_from_b64(QByteArray const &b64_data) const noexcept;
};

#endif