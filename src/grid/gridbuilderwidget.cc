#include "gridbuilderwidget.h"

////////////////////
//  Constructor   //
////////////////////

GridBuilderWidget::GridBuilderWidget(GridWidget *gridwidget, QWidget *parent)
:   QWidget(parent)
{
    d_gridwidget = gridwidget;

    setLayout(new QVBoxLayout);
    layout()->setAlignment(Qt::AlignTop);

    layout()->addWidget(d_details_box = new QGroupBox{"Details"});
    d_details_box->setLayout(new QVBoxLayout);
    d_details_box->layout()->addWidget(d_align_center = new QRadioButton{"Align Center"});
    d_details_box->layout()->addWidget(d_align_vertical = new QRadioButton{"Align Vertical"});
    d_details_box->layout()->addWidget(d_align_horizontal = new QRadioButton{"Align Horizontal"});
    d_details_box->layout()->addWidget(d_dont_align = new QRadioButton{"Don't Align"});
    d_details_box->layout()->addWidget(d_select = new QPushButton{"Select"});
    d_align_center->setChecked(true);

    QObject::connect(d_select, &QPushButton::pressed, this, &GridBuilderWidget::on_select);
    QObject::connect(d_align_center, &QRadioButton::toggled, this, &GridBuilderWidget::on_toggled);
    QObject::connect(d_align_vertical, &QRadioButton::toggled, this, &GridBuilderWidget::on_toggled);
    QObject::connect(d_align_horizontal, &QRadioButton::toggled, this, &GridBuilderWidget::on_toggled);
    QObject::connect(d_dont_align, &QRadioButton::toggled, this, &GridBuilderWidget::on_toggled);
}


GridBuilderWidget::~GridBuilderWidget()
{

}


////////////////////
//  Constructor   //
////////////////////

void GridBuilderWidget::on_select()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select image");
    d_gridwidget->mouse_state().update_pixmap(QPixmap{filename});
    on_toggled(true);
}


void GridBuilderWidget::on_toggled(bool checked)
{
    if(!checked)
        return;
        
    GridMouseState &state = d_gridwidget->mouse_state();

    if (d_align_vertical->isChecked())
        state.update_align_mode(AlignMode::VERTICAL_ALIGN);
    else if (d_align_horizontal->isChecked())
        state.update_align_mode(AlignMode::HORIZONTAL_ALIGN);
    else if (d_dont_align->isChecked())
        state.update_align_mode(AlignMode::NO_ALIGN);
    else
        state.update_align_mode(AlignMode::CENTER_ALIGN);
}