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
    return QCryptographicHash::hash(b64, QCryptographicHash::Sha1).toHex();
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


////////////////////
//     Pixmap     //
////////////////////

QPixmap squared(QPixmap const &pixmap)
{
    if (pixmap.width() == pixmap.height())
        return pixmap;
    
    int maxdim = qMax(pixmap.width(), pixmap.height());
    
    QPixmap newmap{maxdim, maxdim};
    newmap.fill(Qt::transparent);

    int xoffset = (maxdim - pixmap.width()) / 2;
    int yoffset = (maxdim - pixmap.height()) / 2;

    QPainter painter{&newmap};
    painter.drawPixmap(QPoint{xoffset, yoffset}, pixmap);
    return newmap;
}
