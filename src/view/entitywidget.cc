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
    d_entity_widget->layout()->addWidget(d_entity_rotation = new QSlider{Qt::Horizontal});
    d_entity_rotation->setTickPosition(QSlider::TicksBelow);
    d_entity_rotation->setTickInterval(1);
    d_entity_rotation->setRange(-12, 12);
    d_entity_rotation->setValue(0);

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
    QFormLayout *form_layout = new QFormLayout;
    form_widget->setLayout(form_layout);
    form_layout->addRow("Name", d_entity_name = new QLineEdit);
    form_layout->addRow("Size", d_entity_size = new QComboBox);
    d_entity_size->addItems({"Tiny", "Small", "Medium", "Large", "Huge", "Gargantuan"});
    d_entity_size->setCurrentIndex(2);

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
    QObject::connect(d_add_entity, &QPushButton::pressed, this, &EntityWidget::on_add_entity);
    QObject::connect(d_select_file, &QPushButton::pressed, this, &EntityWidget::on_select_file);
    QObject::connect(d_pixmap_drop, &DropWidget::pixmap_dropped, this, &EntityWidget::on_file_dropped);
    QObject::connect(d_entity_list, &QListWidget::itemSelectionChanged, this, &EntityWidget::on_selection_change);
    QObject::connect(d_entity_rotation, &QSlider::sliderMoved, this, &EntityWidget::on_slider_moved);
    QObject::connect(d_entity_rotation, &QSlider::sliderReleased, this, &EntityWidget::on_slider_released);
}


EntityWidget::~EntityWidget()
{

}


void EntityWidget::set_name_prefix(QString const &str)
{
    d_name_prefix = str;
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


void EntityWidget::on_add_entity()
{
    if (d_pixmap_filename.isEmpty())
        return;

    QString name = d_name_prefix + d_entity_name->text() + " " + QString::number(d_unique_number++);
    d_entity_list->addItem(name);
    GridScale scale = static_cast<GridScale>(d_entity_size->currentIndex());

    emit add_entity(name, d_pixmap_filename, scale);
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

    d_entity_rotation->setValue(0);
    emit local_entity_rotation(0);
    emit entity_selection(names);
}


void EntityWidget::on_slider_moved(int value)
{
    emit local_entity_rotation(value * 15);
}


void EntityWidget::on_slider_released()
{
    int value = d_entity_rotation->value();
    if (value == 0)
        return;

    emit entity_rotation(value * 15);
    emit local_entity_rotation(0);
    d_entity_rotation->setValue(0);
}