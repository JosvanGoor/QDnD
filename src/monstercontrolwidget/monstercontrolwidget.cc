#include "monstercontrolwidget.h"

MonsterControlWidget::MonsterControlWidget(QWidget *parent)
:   QWidget(parent)
{
    setLayout(new QVBoxLayout);
    d_selection = -1;

    d_add_box = new QGroupBox{"Add Monster"};
    d_add_box->setLayout(new QVBoxLayout);
    
    QWidget *form_widget = new QWidget;
    QFormLayout *form_layout = new QFormLayout;
    form_layout->addRow("Name", d_name = new QLineEdit);
    form_layout->addRow("Pixmap", d_pixmap_path = new QLineEdit);
    form_widget->setLayout(form_layout);

    d_add_box->layout()->addWidget(form_widget);
    d_add_box->layout()->addWidget(d_select_image = new QPushButton{"Select Image"});
    d_add_box->layout()->addWidget(d_add_monster = new QPushButton{"Add Monster"});

    layout()->addWidget(d_monster_list = new QListWidget);
    layout()->addWidget(d_remove = new QPushButton{"Remove"});
    layout()->addWidget(d_add_box);

    QObject::connect(d_monster_list, &QListWidget::currentRowChanged, this, &MonsterControlWidget::on_selection_changed);
    QObject::connect(d_remove, &QPushButton::pressed, this, &MonsterControlWidget::on_remove);
    QObject::connect(d_select_image, &QPushButton::pressed, this, &MonsterControlWidget::on_select);
    QObject::connect(d_add_monster, &QPushButton::pressed, this, &MonsterControlWidget::on_add);
}


MonsterControlWidget::~MonsterControlWidget()
{

}