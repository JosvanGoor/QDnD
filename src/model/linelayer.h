#ifndef MODEL_LINELAYER_H
#define MODEL_LINELAYER_H

#include <QColor>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLine>
#include <QMap>
#include <QPainter>
#include <QString>
#include <QVector>

struct DrawLine
{
    QColor color;
    QVector<QLine> lines;

    QJsonDocument serialize() const noexcept;
};


class LineLayer
{
    QMap<QString, DrawLine> d_lines;

    public:
        void add_drawline(QJsonObject const &obj);
        void add_drawline(QString const &name, QColor const &color, QVector<QLine> const &lines);
        void remove_drawline(QString const &name);
        void clear();
};

#endif