#include "playerswidget.h"

////////////////////
//  Constructors  //
////////////////////

PlayersWidget::PlayersWidget(QWidget *parent)
:   QWidget(parent)
{
    setLayout(new QVBoxLayout);
    layout()->addWidget(d_scroll_area = new QScrollArea);
    
    QVBoxLayout *scroll_layout = new QVBoxLayout;
    scroll_layout->setAlignment(Qt::AlignTop);
    d_scroll_area->setLayout(scroll_layout);
}


PlayersWidget::~PlayersWidget()
{

}


////////////////////
//     Users      //
////////////////////

void PlayersWidget::add_user(QString const &name, QPixmap const &pixmap, QColor const &color)
{
    QWidget *widget = new QWidget;
    widget->setLayout(new QHBoxLayout);

    QLabel *icon_label = new QLabel;
    icon_label->setPixmap(pixmap.scaled(128, 128));
    QLabel *name_label = new QLabel{name};
    name_label->setStyleSheet("{color: #" + QString::number(color.rgb(), 16) + "}");
    
    widget->layout()->addWidget(icon_label);
    widget->layout()->addWidget(name_label);
    
    d_scroll_area->layout()->addWidget(widget);
    d_portraits[name] = widget;
}


void PlayersWidget::remove_user(QString const &name)
{
    if (auto it = d_portraits.find(name); it != d_portraits.end())
    {
        layout()->removeWidget(it.value());
        delete it.value();
        d_portraits.erase(it);
        update();
    }
}