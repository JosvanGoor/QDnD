#ifndef UTILITY_JSONCONVERSION_H
#define UTILITY_JSONCONVERSION_H

#include <QPair>
#include "../model/player.h"

QJsonObject drawline_to_json(QString const &name, DrawLine const &line);
QPair<QString, DrawLine> json_to_drawline(QJsonObject const &obj);

#endif