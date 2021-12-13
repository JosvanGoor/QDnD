#include "entitywidget.h"

////////////////////
//  Constructors  //
////////////////////

EntityWidget::EntityWidget(QWidget *parent)
:   QWidget(parent)
{
    d_unique_number = 0;

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
    
    QWidget *aligning_widget = new QWidget;
    aligning_widget->setLayout(new QHBoxLayout);
    aligning_widget->layout()->addWidget(d_pixmap_drop = new DropWidget);
    
    QWidget *form_widget = new QWidget;
    form_widget->setLayout(new QHBoxLayout);
    form_widget->layout()->addWidget(new QLabel{"Entity Name:"});
    form_widget->layout()->addWidget(d_entity_name = new QLineEdit);
    
    d_adder_widget->layout()->addWidget(aligning_widget);
    d_adder_widget->layout()->addWidget(form_widget);
    d_adder_widget->layout()->addWidget(d_adder_buttons);

    d_pixmap_drop->set_preferred_size({128, 128});
    d_entity_list->setSelectionMode(QAbstractItemView::ExtendedSelection);

    setLayout(new QVBoxLayout);
    layout()->setAlignment(Qt::AlignTop);
    layout()->addWidget(d_entity_widget);
    layout()->addWidget(d_adder_widget);

    QObject::connect(d_delete_entities, &QPushButton::pressed, this, &EntityWidget::on_delete_entities);
    QObject::connect(d_clear_entities, &QPushButton::pressed, this, &EntityWidget::on_clear_entities);
    QObject::connect(d_add_entity, &QPushButton::pressed, this, &EntityWidget::on_add_entity);
    QObject::connect(d_select_file, &QPushButton::pressed, this, &EntityWidget::on_select_file);
    QObject::connect(d_pixmap_drop, &DropWidget::pixmap_dropped, this, &EntityWidget::on_file_dropped);
    QObject::connect(d_entity_list, &QListWidget::itemSelectionChanged, this, &EntityWidget::on_selection_change);
}


EntityWidget::~EntityWidget()
{

}


////////////////////
//     Slots      //
////////////////////

void EntityWidget::on_delete_entities()
{
    QVector<QString> names;
    QList<QListWidgetItem*> selection = d_entity_list->selectedItems();

    if (selection.isEmpty())
        return;

    for (auto item : selection)
    {
        names.push_back(item->text());
        delete item;
    }

    emit delete_entities(names);
}


void EntityWidget::on_clear_entities()
{
    d_entity_list->clear();
    emit delete_all_entities();
}


void EntityWidget::on_add_entity()
{
    if (d_pixmap_filename.isEmpty())
        return;

    QString name = d_entity_name->text() + " " + QString::number(d_unique_number++);
    d_entity_list->addItem(name);
    emit add_entity(name, d_pixmap_filename);
}


void EntityWidget::on_select_file()
{
    d_pixmap_filename = QFileDialog::getOpenFileName(this, "Select image file");

    QPixmap pixmap{d_pixmap_filename};
    d_pixmap_drop->set_display(pixmap);
}


void EntityWidget::on_file_dropped(QString const &filename)
{
    d_pixmap_filename = filename;
}


void EntityWidget::on_selection_change()
{
    QSet<QString> names;
    QList<QListWidgetItem*> selection = d_entity_list->selectedItems();

    for (auto item : selection)
        names.insert(item->text());

    emit entity_selection(names);
}