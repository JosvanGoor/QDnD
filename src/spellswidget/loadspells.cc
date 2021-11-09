#include "spellswidget.h"

void SpellsWidget::load_spells(QString const &filename)
{
    QString doc;
    QFile file{filename};
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    doc = file.readAll();

    QJsonDocument root = QJsonDocument::fromJson(doc.toUtf8());
    QJsonArray sources = root["sources"].toArray();

    for (QJsonValue const &source : sources)
    {
        QString source_name = source["name"].toString();
        QJsonArray spells = source["spells"].toArray();
        for (QJsonValue const &spell : spells)
            d_spells_list->addItem(new Spell(spell.toObject(), source_name));
    }

    d_spells_list->sortItems();
    d_spells_label->setText("(" + QString::number(d_spells_list->count()) + " found)");
}