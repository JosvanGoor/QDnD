#include "htmlformatting.h"

QString html_bold(QString const &text) noexcept
{
    return "<lab style=\"font-weight: bold;\">" + text + "</lab>";
}


QString html_par(QString const &text, QString const &style) noexcept
{
    if (style == "")
        return "<p>" + text + "</p>";
    else
        return "<p style=\"" + style + "\">" + text + "</p>";
}