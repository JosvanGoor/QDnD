#include "jsonconversion.h"

QJsonObject drawline_to_json(QString const &name, DrawLine const &line)
{
    QJsonArray arr;

    for (auto const &segment : line.line)
    {
        QJsonArray point;
        point.push_back(segment.x1());
        point.push_back(segment.y1());
        arr.push_back(point);
    }

    if (!line.line.isEmpty())
    {
        QJsonArray point;
        point.push_back(line.line.back().x2());
        point.push_back(line.line.back().y2());
        arr.push_back(point);
    }

    QJsonObject obj;
    obj["name"] = name;
    obj["color"] = static_cast<int>(line.color.rgb());
    obj["points"] = arr;
    return obj;
}


QPair<QString, DrawLine> json_to_drawline(QJsonObject const &obj)
{
    QString name = obj["name"].toString();
    DrawLine line;
    line.color = obj["color"].toInt();
    QJsonArray segments = obj["points"].toArray();

    for (int idx = 0; idx < segments.size() - 1; ++idx)
    {
        QJsonArray p1 = segments[idx].toArray();
        QJsonArray p2 = segments[idx + 1].toArray();
        line.line.append(QLine{p1[0].toInt(), p1[1].toInt(), p2[0].toInt(), p2[1].toInt()});
    }

    return {name, line};
}
