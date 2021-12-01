#include "loading.h"

#include <QCryptographicHash>
#include <QFile>
#include <QJsonArray>
#include <QPixmap>

////////////////////
//      Json      //
////////////////////

QString b64_pixmap_hash(QByteArray const &b64)
{
    return QCryptographicHash::hash(b64, QCryptographicHash::Sha1);
}


QPixmap pixmap_from_b64(QByteArray const &b64)
{
    QPixmap pixmap;
    pixmap.loadFromData(QByteArray::fromBase64(b64));
    return pixmap;
}


QJsonDocument load_json_file(QString const &filename)
{
    QFile file{filename};
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    
    return QJsonDocument::fromJson(file.readAll());
}