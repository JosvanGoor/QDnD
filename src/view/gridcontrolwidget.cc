#include "gridcontrolwidget.h"

////////////////////
//  Constructors  //
////////////////////

GridControlWidget::GridControlWidget(GridWidget *grid_widget, QWidget *parent)
:   QWidget(parent)
{
    d_grid_widget = grid_widget;    
    d_grid_widget->set_mouse_mode(MouseMode::MOVE_CHARACTER);

    setLayout(new QVBoxLayout);
    layout()->setAlignment(Qt::AlignTop);

    d_button_widget = new QGroupBox{"Cursor: Walk"};
    d_button_widget->setLayout(new QHBoxLayout);
    d_button_widget->layout()->addWidget(d_walk_button = new QPushButton);
    d_button_widget->layout()->addWidget(d_move_button = new QPushButton);
    d_button_widget->layout()->addWidget(d_ping_button = new QPushButton);
    d_button_widget->layout()->addWidget(d_straight_button = new QPushButton);
    d_button_widget->layout()->addWidget(d_free_button = new QPushButton);

    d_walk_button->setIconSize({32, 32});
    d_walk_button->setIcon(QIcon{QPixmap{":/data/walk_icon.png"}});
    d_move_button->setIconSize({32, 32});
    d_move_button->setIcon(QIcon{QPixmap{":/data/move_icon.png"}});
    d_ping_button->setIconSize({32, 32});
    d_ping_button->setIcon(QIcon{QPixmap{":/data/ping.png"}});
    d_straight_button->setIconSize({32, 32});
    d_straight_button->setIcon(QIcon{QPixmap{":/data/straight_icon.png"}});
    d_free_button->setIconSize({32, 32});
    d_free_button->setIcon(QIcon{QPixmap{":/data/free_icon.png"}});

    d_color_widget = new QGroupBox{"Color"};
    d_color_widget->setLayout(new QHBoxLayout);
    d_color_widget->layout()->addWidget(d_color_display = new ColorDisplay{Qt::black});
    d_color_widget->layout()->addWidget(d_color_pick = new QPushButton{"Pick Color"});
    d_color_display->setMinimumSize(28, 28);
    d_color_display->setMaximumSize(28, 28);

    d_line_control = new QGroupBox{"Line Control"};
    d_line_control->setLayout(new QVBoxLayout);
    d_line_control->layout()->addWidget(d_line_list = new QListWidget);
    d_line_control->layout()->addWidget(d_delete_lines = new QPushButton{"Delete selection"});
    d_line_control->layout()->addWidget(d_clear_lines = new QPushButton{"Clear all lines"});
    d_line_list->setSelectionMode(QAbstractItemView::ExtendedSelection);

    layout()->addWidget(d_button_widget);
    layout()->addWidget(d_color_widget);
    layout()->addWidget(d_reset_position = new QPushButton{"Jump to (0,0)"});
    layout()->addWidget(d_line_control);

    QObject::connect(d_walk_button, &QPushButton::pressed, this, &GridControlWidget::on_button_pressed);
    QObject::connect(d_move_button, &QPushButton::pressed, this, &GridControlWidget::on_button_pressed);
    QObject::connect(d_ping_button, &QPushButton::pressed, this, &GridControlWidget::on_button_pressed);
    QObject::connect(d_straight_button, &QPushButton::pressed, this, &GridControlWidget::on_button_pressed);
    QObject::connect(d_free_button, &QPushButton::pressed, this, &GridControlWidget::on_button_pressed);
    QObject::connect(d_color_pick, &QPushButton::pressed, this, &GridControlWidget::on_color_selection);
    QObject::connect(d_reset_position, &QPushButton::pressed, this, &GridControlWidget::on_reset_position);
    QObject::connect(d_delete_lines, &QPushButton::pressed, this, &GridControlWidget::on_delete_lines);
    QObject::connect(d_clear_lines, &QPushButton::pressed, this, &GridControlWidget::on_clear_lines);
    QObject::connect(d_line_list, &QListWidget::itemSelectionChanged, this, &GridControlWidget::on_selection_changed);
}


GridControlWidget::~GridControlWidget()
{

}


////////////////////
//     Slots      //
////////////////////

void GridControlWidget::on_reset_position()
{
    d_grid_widget->reset_offset();
}


void GridControlWidget::on_color_selection()
{
    QColor selection = QColorDialog::getColor(d_color_display->color(), this);
    if (selection.isValid())
    {
        d_color_display->set_color(selection);
        d_grid_widget->set_draw_color(selection);
    }
}


void GridControlWidget::on_button_pressed()
{
    QObject *sender = QObject::sender();

    if (sender == d_walk_button)
    {
        d_grid_widget->set_mouse_mode(MouseMode::MOVE_CHARACTER);
        d_button_widget->setTitle("Cursor: Walk");
    }
    else if (sender == d_move_button)
    {
        d_grid_widget->set_mouse_mode(MouseMode::MOVE_GRID);
        d_button_widget->setTitle("Cursor: Move Grid");
    }
    else if (sender == d_ping_button)
    {
        d_grid_widget->set_mouse_mode(MouseMode::PING);
        d_button_widget->setTitle("Cursor: Ping");
    }
    else if (sender == d_straight_button)
    {
        d_grid_widget->set_mouse_mode(MouseMode::LINE_DRAW);
        d_button_widget->setTitle("Cursor: Line Draw");
    }
    else if (sender == d_free_button)
    {
        d_grid_widget->set_mouse_mode(MouseMode::FREE_DRAW);
        d_button_widget->setTitle("Cursor: Free Draw");
    }
}


void GridControlWidget::on_clear_lines()
{
    d_line_list->clear();
    emit lines_cleared();
}


void GridControlWidget::on_delete_lines()
{
    QVector<QString> names;
    QList<QListWidgetItem*> selection = d_line_list->selectedItems();

    if (selection.size() == 0)
        return;

    for (auto &item : selection)
    {
        names.push_back(item->text());
        delete item;
    }
    
    emit lines_removed(names);
}


void GridControlWidget::on_selection_changed()
{
    QSet<QString> names;
    QList<QListWidgetItem*> selection = d_line_list->selectedItems();

    for (auto &item : selection)
        names.insert(item->text());
    
    emit line_selection_changed(names);
}


////////////////////
//     Slots      //
////////////////////

void GridControlWidget::register_line(QString const &name)
{
    d_line_list->addItem(name);
}