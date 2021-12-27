#include "mapmanagercontrolwidget.h"

////////////////////
//  Constructors  //
////////////////////

MapManagerControlWidget::MapManagerControlWidget(MapManager *manager, QWidget *parent)
:   QWidget(parent)
{
    d_manager = nullptr;
    setLayout(new QVBoxLayout);

    QGroupBox *group_box = new QGroupBox{"Item Groups"};
    group_box->setLayout(new QVBoxLayout);
    group_box->layout()->addWidget(d_group_list = new QListWidget);
    d_group_list->setSelectionMode(QAbstractItemView::SingleSelection);
    layout()->addWidget(group_box);

    group_box = new QGroupBox{"Settings"};
    group_box->setLayout(new QFormLayout);
    reinterpret_cast<QFormLayout*>(group_box->layout())->addRow("Visible", d_visibility_check = new QCheckBox);
    layout()->addWidget(group_box);

    group_box = new QGroupBox{"New Group"};
    group_box->setLayout(new QVBoxLayout);
    group_box->layout()->addWidget(d_new_group_name = new QLineEdit);
    group_box->layout()->addWidget(d_new_group_button = new QPushButton{"Add"});
    layout()->addWidget(group_box);

    layout()->addWidget(d_save_map = new QPushButton{"Save Map"});
    layout()->addWidget(d_load_map = new QPushButton{"Load Map"});
    layout()->addWidget(d_insert_map = new QPushButton{"Insert Map"});

    QObject::connect(d_new_group_button, &QPushButton::pressed, this, &MapManagerControlWidget::on_group_added);
    QObject::connect(d_visibility_check, &QCheckBox::clicked, this, &MapManagerControlWidget::on_visibility_changed);
    QObject::connect(d_group_list, &QListWidget::itemSelectionChanged, this, &MapManagerControlWidget::on_selection_changed);
    QObject::connect(d_save_map, &QPushButton::pressed, this, &MapManagerControlWidget::on_save_map);
    QObject::connect(d_load_map, &QPushButton::pressed, this, &MapManagerControlWidget::on_load_map);

    d_manager = manager;
    for (auto &group : d_manager->grid_groups())
        d_group_list->addItem(group.name());
}


MapManagerControlWidget::~MapManagerControlWidget()
{ }


////////////////////
//     Slots      //
////////////////////

void MapManagerControlWidget::on_group_added()
{
    if (!d_manager)
        return;
    
    if (d_new_group_name->text().isEmpty())
        return;

    d_manager->add_group(d_new_group_name->text());
    d_group_list->addItem(d_new_group_name->text());
    d_new_group_name->setText("");
}


void MapManagerControlWidget::on_selection_changed()
{
    QListWidgetItem *selection = d_group_list->currentItem();
    d_manager->set_selection(selection->text());

    if (d_manager->selected_group().visibility_mode() == VisibilityMode::VISIBLE)
        d_visibility_check->setChecked(true);
    else
        d_visibility_check->setChecked(false);
}


void MapManagerControlWidget::on_visibility_changed([[maybe_unused]] bool checked)
{
    emit group_visibility_changed(d_manager->selected_group_name(), d_visibility_check->isChecked() ? VisibilityMode::VISIBLE : VisibilityMode::HIDDEN);
}


void MapManagerControlWidget::on_save_map()
{
    QString filename = QFileDialog::getSaveFileName(this, "Choose Save Location...");
    if (filename.isEmpty())
        return;

    QJsonObject obj;
    obj["type"] = "QDND_MAP_1.0A";
    obj["groups"] = d_manager->jsonify_map(true);
    QJsonDocument document{obj};

    QFile file{filename};
    file.open(QIODevice::WriteOnly);
    file.write(document.toJson());
}


void MapManagerControlWidget::on_load_map()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose file to load from.");
    if (filename.isEmpty())
        return;

    QFile file{filename};
    file.open(QIODevice::ReadOnly);
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());

    if (document["type"].toString() != "QDND_MAP_1.0A")
        return; // illegal file, no error? not my problim

    d_manager->clean_from_json(document.object());

    d_group_list->clear();
    for (auto const &group : d_manager->grid_groups())
        d_group_list->addItem(group.name());
}