#include "itemgroupcontrolwidget.h"

////////////////////
//  Constructors  //
////////////////////

ItemGroupControlWidget::ItemGroupControlWidget(GridWidget *grid, MapManager *manager, QWidget *parent)
:   QWidget(parent)
{
    d_grid = grid;
    d_manager = manager;
    d_current_mode = MouseMode::GRID_ITEM_PLACEMENT;
    
    setLayout(new QVBoxLayout);
    layout()->setAlignment(Qt::AlignTop);

    QWidget *button_widget = new QWidget;
    button_widget->setLayout(new QHBoxLayout);
    button_widget->layout()->addWidget(d_placement_mode = new QPushButton);
    button_widget->layout()->addWidget(d_selection_mode = new QPushButton);

    QWidget *snap_form_widget = new QWidget;
    QFormLayout *snap_form = new QFormLayout;
    snap_form->addRow("Snap Horizontal", d_snap_horizontal_check = new QCheckBox);
    snap_form->addRow("Snap Vertical", d_snap_vertical_check = new QCheckBox);
    snap_form->addRow("ypos Offset", d_snap_xoffset_check = new QCheckBox);
    snap_form->addRow("xpos Offset", d_snap_yoffset_check = new QCheckBox);
    snap_form_widget->setLayout(snap_form);

    d_mouse_mode = new QGroupBox{"Mouse Mode: Placement"};
    d_mouse_mode->setLayout(new QVBoxLayout);
    d_mouse_mode->layout()->addWidget(button_widget);
    d_mouse_mode->layout()->addWidget(snap_form_widget);

    d_placement_mode->setIconSize({32, 32});
    d_placement_mode->setIcon(QIcon{QPixmap{":data/placeitem.png"}});
    d_selection_mode->setIconSize({32, 32});
    d_selection_mode->setIcon(QIcon{QPixmap{":data/select.png"}});

    QWidget *centering_widget = new QWidget;
    centering_widget->setLayout(new QHBoxLayout);
    centering_widget->layout()->addWidget(d_pixmap_selection = new DropWidget);
    d_pixmap_selection->set_preferred_size({128, 128});

    QWidget *form_widget = new QWidget;
    QFormLayout *form_layout = new QFormLayout;
    QWidget *rota_widget = new QWidget;
    rota_widget->setLayout(new QHBoxLayout);
    rota_widget->layout()->addWidget(d_rotation_slider = new QSlider{Qt::Horizontal});
    rota_widget->layout()->addWidget(d_rotation_label = new QLabel{"0"});
    form_widget->setLayout(form_layout);
    // form_layout->addRow("x Position", d_xpos_edit = new QLineEdit);
    // form_layout->addRow("y Position", d_ypos_edit = new QLineEdit);
    form_layout->addRow("Rotation", rota_widget);
    form_layout->addRow("Scale", d_scale_selection = new QComboBox);
    d_rotation_slider->setRange(0, 24);
    d_rotation_slider->setTickInterval(1);
    d_scale_selection->addItems({"Tiny", "Small", "Medium", "Large", "Huge", "Gargantuan"});
    d_scale_selection->setCurrentIndex(2);

    d_current_item = new QGroupBox{"Current Item"};
    d_current_item->setLayout(new QVBoxLayout);
    d_current_item->layout()->addWidget(centering_widget);
    d_current_item->layout()->addWidget(form_widget);

    layout()->addWidget(d_group_name = new QLabel{"Current Group: " + d_manager->selected_group_name()});
    layout()->addWidget(d_mouse_mode);
    layout()->addWidget(d_current_item);
    layout()->addWidget(d_remove_item = new QPushButton{"Remove Selected"});

    QObject::connect(d_placement_mode, &QPushButton::pressed, this, &ItemGroupControlWidget::on_mouse_mode_changed);
    QObject::connect(d_selection_mode, &QPushButton::pressed, this, &ItemGroupControlWidget::on_mouse_mode_changed);
    QObject::connect(d_snap_horizontal_check, &QCheckBox::toggled, this, &ItemGroupControlWidget::on_snap_changed);
    QObject::connect(d_snap_vertical_check, &QCheckBox::toggled, this, &ItemGroupControlWidget::on_snap_changed);
    QObject::connect(d_snap_xoffset_check, &QCheckBox::toggled, this, &ItemGroupControlWidget::on_snap_changed);
    QObject::connect(d_snap_yoffset_check, &QCheckBox::toggled, this, &ItemGroupControlWidget::on_snap_changed);
    QObject::connect(d_pixmap_selection, &DropWidget::pixmap_dropped, this, &ItemGroupControlWidget::on_pixmap_dropped);
    QObject::connect(d_rotation_slider, &QSlider::valueChanged, this, &ItemGroupControlWidget::on_rotation_changed);
    QObject::connect(d_scale_selection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ItemGroupControlWidget::on_scale_changed);
    QObject::connect(d_remove_item, &QPushButton::pressed, this, &ItemGroupControlWidget::on_remove);
    
    QObject::connect(d_grid, &GridWidget::grid_item_placed, this, &ItemGroupControlWidget::on_grid_item_click);
    QObject::connect(d_grid, &GridWidget::selection_click, this, &ItemGroupControlWidget::on_grid_selection_click);
    QObject::connect(d_grid, &GridWidget::selection_rclick, this, &ItemGroupControlWidget::on_grid_selection_rclick);
    QObject::connect(d_manager, &MapManager::selection_changed, this, &ItemGroupControlWidget::on_group_selection_changed);
}


ItemGroupControlWidget::~ItemGroupControlWidget()
{ }


////////////////////
//    Utility     //
////////////////////

void ItemGroupControlWidget::reset_mouse_mode()
{
    d_grid->set_mouse_mode(d_current_mode);
}


////////////////////
//     Slots      //
////////////////////

void ItemGroupControlWidget::on_snap_changed([[maybe_unused]] bool checked)
{
    d_grid->set_snap_modes
    (
        d_snap_horizontal_check->isChecked(),
        d_snap_vertical_check->isChecked(),
        d_snap_xoffset_check->isChecked(),
        d_snap_yoffset_check->isChecked()
    );
}


void ItemGroupControlWidget::on_mouse_mode_changed()
{
    QObject *sender = QObject::sender();

    if (sender == d_placement_mode)
    {
        d_current_mode = MouseMode::GRID_ITEM_PLACEMENT;
        d_mouse_mode->setTitle("Mouse Mode: Placement");
    }
    else if (sender == d_selection_mode)
    {
        d_current_mode = MouseMode::GRID_ITEM_SELECTION;
        d_mouse_mode->setTitle("Mouse Mode: Selection");
    }

    clear_selection();
    reset_mouse_mode();
}


void ItemGroupControlWidget::on_pixmap_dropped(QString const &filename)
{
    QPixmap pixmap{filename};
    pixmap = squared(pixmap);
    d_grid->update_gi_pixmap(pixmap);
    d_pixmap_filename = filename;
}


void ItemGroupControlWidget::on_rotation_changed(int value)
{
    d_rotation_label->setText(QString::number(value * 15));
    d_grid->update_gi_rotation(value * 15);
}


void ItemGroupControlWidget::on_scale_changed(int index)
{
    d_grid->update_gi_scale(static_cast<GridScale>(index));
}


void ItemGroupControlWidget::on_remove()
{
    if (d_selection == -1)
        return;

    emit remove_grid_item(d_selection);
    clear_selection();
}


void ItemGroupControlWidget::on_group_selection_changed()
{
    clear_selection();
    d_group_name->setText("Current Group: " + d_manager->selected_group_name());
}


void ItemGroupControlWidget::on_grid_item_click(QPoint const &position)
{
    if (d_pixmap_filename.isEmpty())
        return;

    emit place_grid_item
    (
        d_pixmap_filename,
        position,
        d_rotation_slider->value() * 15,
        static_cast<GridScale>(d_scale_selection->currentIndex()),
        VisibilityMode::PARENT
    );
}


void ItemGroupControlWidget::clear_selection()
{
    d_selection = 0;
    d_grid->update_gi_selected(false);
    emit debug_message("selection cleared?");
}


void ItemGroupControlWidget::on_grid_selection_click(QPoint const &position)
{
    debug_message("on_grid_selection_click");
    QVector<GridItem> &items = d_manager->selected_group().items();
    for (int idx = 0; idx != items.size(); ++idx)
    {
        int dims = scale(items[idx].scale) * 64;
        QRect rect{items[idx].position, QSize{dims, dims}};
        if (rect.contains(position))
        {
            d_selection = idx;
            d_grid->update_gi_selected(true, rect.topLeft());
            d_grid->update_gi_scale(items[idx].scale);
            d_grid->update_gi_rotation(items[idx].rotation);
            return;
        }
    }

    clear_selection();
}


void ItemGroupControlWidget::on_grid_selection_rclick()
{
    clear_selection();
}