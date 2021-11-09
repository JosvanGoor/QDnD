#include "spell.h"

QString Spell::string_classes(QJsonArray const &classes)
{
    QString rval;

    for (auto val : classes)
    {
        if (rval == "")
            rval.append(val.toString());
        else
        {
            rval.append(", ");
            rval.append(val.toString());
        }   
    }

    return rval;
}


QString Spell::string_components(QJsonObject const &components)
{
    auto append = [](QString &dest, QString const &app)
    {
        if (dest == "")
            dest.append(app);
        else
        {
            dest.append(", ");
            dest.append(app);
        }
    };

    QString rval;

    if (components["verbal"].toBool())
        append(rval, "V");
    if (components["somatic"].toBool())
        append(rval, "S");
    if (components["material"].toBool())
    {
        append(rval, "M");
        rval.append(" (" + components["materials"].toString() + ")");
    }

    return rval;
}


QString Spell::string_description(QJsonObject const &description)
{
    QString rval;

    rval.append(html_par
    (
        description["description"].toString(),
        "color: black;"
    ));

    for (auto extra : description["additional"].toArray())
    {
        rval.append(html_par
        (
            html_bold(extra.toObject()["header"].toString() + ". ")
                + extra.toObject()["text"].toString(),
            "color: black;"
        ));
    }

    // sanitize newlines
    rval.replace(QRegularExpression{"\\n"}, "<br>");
    return rval;
}