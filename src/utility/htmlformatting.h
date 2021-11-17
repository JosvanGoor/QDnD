#ifndef UTILITY_HTMLFORMATTING_H
#define UTILITY_HTMLFORMATTING_H

#include <QString>

QString html_bold(QString const &text) noexcept;
QString html_par(QString const &text, QString const &style) noexcept;

#endif