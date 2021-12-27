#ifndef UTILITY_LOADING_H
#define UTILITY_LOADING_H

#include <QByteArray>
#include <QJsonDocument>
#include <QPainter>
#include <QString>

QString b64_pixmap_hash(QByteArray const &b64);
QPixmap pixmap_from_b64(QByteArray const &b64);
QJsonDocument load_json_file(QString const &filename);

QPixmap squared(QPixmap const &pixmap);

#endif