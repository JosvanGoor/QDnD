#include "entitywidget.h"

////////////////////
//  Constructors  //
////////////////////

EntityWidget::EntityWidget(QWidget *parent)
:   QWidget(parent)
{
    d_entity_widget = new QGroupBox{"Entities"};
    d_entity_widget->setLayout(new QVBoxLayout);
    d_entity_widget->layout()->addWidget(d_entity_list = new QListWidget);
    d_entity_widget->layout()->addWidget(d_delete_entities = new QPushButton{"Delete Selected"});
    d_entity_widget->layout()->addWidget(d_clear_entities = new QPushButton{"Clear Entities"});

    d_adder_buttons = new QWidget;
    d_adder_buttons->setLayout(new QHBoxLayout);
    d_adder_buttons->layout()->addWidget(d_add_entity = new QPushButton{"Add Entity"});
    d_adder_buttons->layout()->addWidget(d_select_file = new QPushButton{"Select Token"});

    d_adder_widget = new QGroupBox{"Add Entity"};
    d_adder_widget->setLayout(new QVBoxLayout);
    d_adder_widget->layout()->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    // d_adder_widget->layout()->addWidget(d_pixmap_drop = new DropWidget);
    QWidget *aligning_widget = new QWidget;
    aligning_widget->setLayout(new QHBoxLayout);
    aligning_widget->layout()->addWidget(d_pixmap_drop = new DropWidget);
    d_adder_widget->layout()->addWidget(aligning_widget);
    d_adder_widget->layout()->addWidget(d_entity_name = new QLineEdit);
    d_adder_widget->layout()->addWidget(d_adder_buttons);

    d_pixmap_drop->set_preferred_size({128, 128});

    setLayout(new QVBoxLayout);
    layout()->setAlignment(Qt::AlignTop);
    layout()->addWidget(d_entity_widget);
    layout()->addWidget(d_adder_widget);
}


EntityWidget::~EntityWidget()
{

}