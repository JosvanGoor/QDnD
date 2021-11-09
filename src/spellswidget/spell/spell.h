#ifndef SPELLSWIDGET_SPELL_H
#define SPELLSWIDGET_SPELL_H

#include <QJsonArray>
#include <QJsonObject>
#include <QListWidgetItem>
#include <QString>

class Spell : public QListWidgetItem
{
    QString d_name;
    QString d_source;
    int d_level;
    bool d_ritual;
    QString d_range;
    QString d_casting_time;
    QString d_duration;
    QString d_components;
    QString d_school;
    QString d_classes;
    QString d_description;

    public:
        explicit Spell(QJsonObject const &object, QString const &source = "Unknown");

        // getters
        QString const &name() const noexcept;
        QString const &source() const noexcept;
        int level() const noexcept;
        bool is_ritual() const noexcept;
        QString const &range() const noexcept;
        QString const &casting_time() const noexcept;
        QString const &components() const noexcept;
        QString const &school() const noexcept;
        QString const &classes() const noexcept;
        QString const &description() const noexcept;

        static QString html_bold(QString const &text) noexcept;
        static QString html_par(QString const &text, QString const &style) noexcept;
        QString formatted_description() const noexcept;

    private:
        QString string_classes(QJsonArray const &classes);
        QString string_components(QJsonObject const &components);
        QString string_description(QJsonObject const &description);


};

#endif