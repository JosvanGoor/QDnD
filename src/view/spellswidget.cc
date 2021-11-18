#include "spellswidget.h"

#include <QFormLayout>
#include <QVBoxLayout>

////////////////////
//  Constructors  //
////////////////////

SpellsWidget::SpellsWidget(QWidget *parent)
:   QSplitter(parent)
{
    // list stuff
    d_list_widget = new QWidget;
    d_list_widget->setLayout(new QVBoxLayout);
    d_spells_label = new QLabel("Spells: (0 found)");
    d_spells_list = new QListWidget;
    
    d_list_widget->layout()->addWidget(d_spells_label);
    d_list_widget->layout()->addWidget(d_spells_list);
    this->addWidget(d_list_widget);

    // description stuff
    d_description_widget = new QWidget;
    d_description_widget->setLayout(new QVBoxLayout);
    d_search = new QLineEdit;
    d_description = new QTextEdit;

    QWidget *form_widget = new QWidget;
    QFormLayout *form_layout = new QFormLayout;
    form_layout->addRow("Search: ", d_search);
    form_widget->setLayout(form_layout);
    
    d_description->setStyleSheet("border-image: url(:data/paper.jpg);");
    d_description->setFont(QFont("arial", 14));
    d_description->setReadOnly(true);

    d_description_widget->layout()->addWidget(form_widget);
    d_description_widget->layout()->addWidget(d_description);
    
    this->addWidget(d_description_widget);
    this->setSizes({200, 600});

    QObject::connect(d_search, &QLineEdit::textChanged, this, &SpellsWidget::on_search_change);
    QObject::connect(d_spells_list, &QListWidget::currentRowChanged, this, &SpellsWidget::on_selection_change);
}


SpellsWidget::~SpellsWidget()
{

}


////////////////////
//     Public     //
////////////////////

void SpellsWidget::add_spell(QString const &name) noexcept
{
    d_spells_list->addItem(name);
    d_spells_list->sortItems();
    on_search_change(d_search->text());
}


void SpellsWidget::show_description(QString const &description) noexcept
{
    d_description->setHtml(description);
}


////////////////////
//     Slots      //
////////////////////

void SpellsWidget::on_search_change(QString const &term)
{
    size_t shown = 0;

    for (int idx = 0; idx < d_spells_list->count(); ++idx)
    {
        if (d_spells_list->item(idx)->text().contains(term, Qt::CaseInsensitive))
        {
            d_spells_list->item(idx)->setHidden(false);
            ++shown;
        }
        else
            d_spells_list->item(idx)->setHidden(true);
    }

    d_spells_label->setText("(" + QString::number(shown) + " found).");
}


void SpellsWidget::on_selection_change(int selected)
{
    if (selected == -1)
        return;

    emit selection_changed(d_spells_list->item(selected)->text());
}