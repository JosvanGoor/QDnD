#include "userswidget.h"

UsersWidget::UsersWidget(QWidget *parent)
:   QWidget()
{
    setLayout(new QVBoxLayout);
    layout()->setAlignment(Qt::AlignTop);

    QPixmap pixmap{":/data/dmpic.png"};
    add_user("Dungeon Master", pixmap);
}


UsersWidget::~UsersWidget()
{

}


void UsersWidget::add_user(QString const &name, QPixmap const &pixmap)
{
    QPixmap icon = pixmap.scaled(128, 128);

    QWidget *widget = new QWidget;
    widget->setLayout(new QHBoxLayout);

    QLabel *icon_label = new QLabel;
    icon_label->setPixmap(icon);
    widget->layout()->addWidget(icon_label);
    widget->layout()->addWidget(new QLabel{name});

    layout()->addWidget(widget);
    d_users[name] = widget;
}


void UsersWidget::remove_user(QString const &name)
{
    if (auto it = d_users.find(name); it != d_users.end())
    {
        layout()->removeWidget(it.value());
        delete it.value();
        d_users.erase(it);
        update();
    }
    else
    {
        std::cout << "Can't find name " << name.toStdString() << "\n" << std::flush;
    }
}