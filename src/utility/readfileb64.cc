#include "utility.h"

QString read_file_conditionally_b64(QString path)
{
    if (path.isEmpty())
        return "";

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return "";

    QByteArray data = file.readAll();
    return data.toBase64();
}