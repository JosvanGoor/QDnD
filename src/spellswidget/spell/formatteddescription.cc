#include "spell.h"

#include <QTextStream>

QString Spell::html_bold(QString const &text) noexcept
{
    return QString{"<lab style=\"font-weight: bold;\">"} + text + "</lab>";
}


QString Spell::html_par(QString const &text, QString const &style) noexcept
{
    if (style == "")
        return QString{"<p>"} + text + QString{"</p>"};
    else
        return QString{"<p style=\""} + style + "\">" + text + QString{"</p>"};
}


QString Spell::formatted_description() const noexcept
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
