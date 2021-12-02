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
    if (d_portraits.find(name) != d_portraits.end())
        return;

    QWidget *widget = new QWidget;
    widget->setLayout(new QHBoxLayout);

    QLabel *icon_label = new QLabel;
    icon_label->setMinimumSize({128, 128});
    icon_label->setPixmap(pixmap.scaled(128, 128));
    QLabel *name_label = new QLabel{name};
    name_label->setStyleSheet("{color: #" + QString::number(color.rgb(), 16) + "}");
    
    widget->layout()->addWidget(icon_label);
    widget->layout()->addWidget(name_label);
    
    d_scroll_area->layout()->addWidget(widget);
    d_portraits[name] = {"", widget, icon_label};
}


void PlayersWidget::add_user(QString const &name, QString const &key, QColor const &color)
{
    if (d_portraits.find(name) != d_portraits.end())
        return;

    QWidget *widget = new QWidget;
    widget->setLayout(new QHBoxLayout);

    QLabel *icon_label = new QLabel;
    icon_label->setMinimumSize({128, 128});
    QLabel *name_label = new QLabel{name};
    name_label->setStyleSheet("{color: #" + QString::number(color.rgb(), 16) + "}");
    
    widget->layout()->addWidget(icon_label);
    widget->layout()->addWidget(name_label);
    
    d_scroll_area->layout()->addWidget(widget);
    d_portraits[name] = {key, widget, icon_label};
}


void PlayersWidget::remove_user(QString const &name)
{
    if (auto it = d_portraits.find(name); it != d_portraits.end())
    {
        layout()->removeWidget(it.value().widget_ptr);
        delete it.value().widget_ptr;
        d_portraits.erase(it);
        update();
    }
}


////////////////////
//     Slots      //
////////////////////

void PlayersWidget::pixmap_received(QString const &key, QPixmap const &pixmap)
{
    for (auto &[req_key, _, iconptr] : d_portraits)
    {
        if (req_key == key)
        {
            iconptr->setPixmap(pixmap.scaled(128, 128));
            req_key = "";
            return;
        }
    }
}