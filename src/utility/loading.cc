#include "loading.h"

#include <QFile>
#include <QJsonArray>

////////////////////
//      Json      //
////////////////////

QJsonDocument load_json_file(QString const &filename)
{
    QFile file{filename};
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    
    return QJsonDocument::fromJson(file.readAll());
}