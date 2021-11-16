#include "gridcontrolwidget.h"

GridControlWidget::GridControlWidget(QWidget *parent)
:   QWidget(parent)
{
    d_selection = -1;

    d_mode_group = new QGroupBox{"Grid Mouse Mode"};
    d_mode_group->setLayout(new QVBoxLayout);
    d_mode_group->layout()->addWidget(d_draw = new QRadioButton{"Draw"});
    d_mode_group->layout()->addWidget(d_select = new QRadioButton{"Select"});

    d_reset_group = new QGroupBox{"Grid Reset"};
    d_reset_group->setLayout(new QVBoxLayout);
    d_reset_group->layout()->addWidget(d_reset_position = new QPushButton{"Reset Position"});
    d_reset_group->layout()->addWidget(d_clear_lines = new QPushButton{"Clear Lines"});
    d_reset_group->layout()->addWidget(d_clear_grid = new QPushButton{"Clear Grid"});

    d_lines_group = new QGroupBox{"Grid Lines"};
    d_lines_group->setLayout(new QVBoxLayout);
    d_lines_group->layout()->addWidget(d_lines_list = new QListWidget);
    d_lines_group->layout()->addWidget(d_delete = new QPushButton{"Delete"});
    d_lines_group->layout()->addWidget(d_unselect = new QPushButton{"Unselect"});

    d_select->setChecked(true);

    setLayout(new QVBoxLayout);
    layout()->addWidget(d_mode_group);
    layout()->addWidget(d_reset_group);
    layout()->addWidget(d_lines_group);

    QObject::connect
    (
        d_delete,
        &QPushButton::pressed,
        this,
        &GridControlWidget::on_delete_line
    );

    QObject::connect
    (
        d_lines_list,
        &QListWidget::currentRowChanged,
        this,
        &GridControlWidget::on_selection_changed
    );

    QObject::connect
    (
        d_unselect,
        &QPushButton::pressed,
        this,
        &GridControlWidget::on_unselect
    );

    QObject::connect
    (
        d_reset_position,
        &QPushButton::pressed,
        this,
        &GridControlWidget::on_reset_position
    );
}


GridControlWidget::~GridControlWidget()
{

}