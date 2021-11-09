#include "spellswidget.h"

void SpellsWidget::on_search_change(QString const &term)
{
    size_t shown = 0;
    
    for (int idx = 0; idx < d_spells_list->count(); ++idx)
    {
        Spell *spell = dynamic_cast<Spell*>(d_spells_list->item(idx));
        if (spell->name().contains(term, Qt::CaseInsensitive))
        {
            spell->setHidden(false);
            ++shown;
        }
        else
            spell->setHidden(true);
    }

    d_spells_label->setText("(" + QString::number(shown) + " found)");
}


void SpellsWidget::on_selection_change(int selected)
{
    if (selected == -1)
        return;

    Spell *spell = dynamic_cast<Spell*>(d_spells_list->item(selected));
    d_description->setHtml(spell->formatted_description());
}