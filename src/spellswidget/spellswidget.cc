#include "spellswidget.h"

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
    d_spell_search = new QLineEdit;
    d_description = new QTextEdit;

    QWidget *form_widget = new QWidget;
    QFormLayout *form_layout = new QFormLayout;
    form_layout->addRow("Search: ", d_spell_search);
    form_widget->setLayout(form_layout);
    
    d_description->setStyleSheet("border-image: url(:data/paper.jpg);");
    d_description->setFont(QFont("arial", 14));
    d_description->setReadOnly(true);

    d_description_widget->layout()->addWidget(form_widget);
    d_description_widget->layout()->addWidget(d_description);
    this->addWidget(d_description_widget);

    // load spells
    load_spells(":data/spells.json");

    // connect signals & slots
    QObject::connect
    (
        d_spells_list,
        &QListWidget::currentRowChanged,
        this,
        &SpellsWidget::on_selection_change
    );

    QObject::connect
    (
        d_spell_search,
        &QLineEdit::textEdited,
        this,
        &SpellsWidget::on_search_change
    );

    // panel setup
    this->setSizes({200, 600});
    adjustSize();
}


SpellsWidget::~SpellsWidget()
{

}