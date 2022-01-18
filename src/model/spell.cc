#include "spell.h"

//////////////////
//  Constructor //
//////////////////

Spell::Spell()
{ }

Spell::Spell(QJsonObject const &object, QString const &source)
{
    d_source = source;
    d_name = object["name"].toString();
    d_level = object["level"].toInt();
    d_ritual = object["ritual"].toBool();
    d_range = object["range"].toString();
    d_casting_time = object["casting_time"].toString();
    d_duration = object["duration"].toString();
    d_components = parse_components(object["components"].toObject());
    d_school = object["school"].toString();
    d_classes = parse_classes(object["classes"].toArray());
    d_description = parse_description(object["description"].toObject());
}


//////////////////
//   Getters    //
//////////////////

QString Spell::name() const noexcept
{
    return d_name;
}


QString Spell::format() const noexcept
{
    QString rval;
    QTextStream sin{&rval};

    sin << "<h1 style = \"color: rgb(180, 21, 28);\">";
    sin << d_name << "</h1>";

    sin << "<p style =\"color: black; font-style: italic;\">";
    sin << "Source: " << d_source << "</p>";

    QString level = (d_level == 0 ? "cantrip" : QString::number(d_level));
    sin << html_par(html_bold("Level: ") + level, "color: black;");
    sin << html_par(html_bold("Ritual: ") + (d_ritual ? "Yes!" : "No"), "color: black;");
    sin << html_par(html_bold("Range: ") + d_range, "color: black;");
    sin << html_par(html_bold("Casting Time: ") + d_casting_time, "color: black;");
    sin << html_par(html_bold("Duration: ") + d_duration, "color: black;");
    sin << html_par(html_bold("Components: ") + d_components, "color: black;");
    sin << html_par(html_bold("School: ") + d_school, "color: black;");
    sin << html_par(html_bold("Classes: ") + d_classes, "color: black;");
    sin << html_par(d_description, "color: black;");

    return rval;
}


//////////////////
//   Parsing    //
//////////////////

QString Spell::parse_classes(QJsonArray const &classes) noexcept
{
    QString rval;

    if (!classes.isEmpty())
        rval.append(classes[0].toString());

    for (int idx = 1; idx < classes.size(); ++idx)
        rval += ", " + classes[idx].toString();

    return rval;
}


QString Spell::parse_components(QJsonObject const &object) noexcept
{
    QString rval;

    if (object["verbal"].toBool())
        rval += "V";
    if (object["somatic"].toBool())
        rval += rval.isEmpty() ? "S" : ", S";
    if (object["material"].toBool())
        rval += rval.isEmpty() ? "M (" : ", M (" +  object["materials"].toString() + ")";
    
    return rval;
}


QString Spell::parse_description(QJsonObject const &object) noexcept
{
    QString rval;

    rval.append(html_par(object["description"].toString(), "color: black"));

    QJsonArray additional = object["additional"].toArray();
    for (auto const &extra : additional)
    {
        QJsonObject info = extra.toObject();
        QString head = info["header"].toString() + ". ";
        head = head == ". " ? "" : html_bold(head);
        
        rval.append(html_par(head + info["text"].toString(), "color: black;"));
    }

    rval.replace(QRegularExpression{"\\n"}, "<br>");
    return rval;
}