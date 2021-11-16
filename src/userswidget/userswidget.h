#ifndef USERS_WIDGET_H
#define USERS_WIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include <QVBoxLayout>
#include <QWidget>
#include <QPixmap>

#include <iostream>

class UsersWidget : public QWidget
{
    Q_OBJECT

    QMap<QString, QWidget*> d_users;

    public:
        explicit UsersWidget(QWidget *parent = nullptr);
        ~UsersWidget();

        void add_user(QString const &name, QPixmap const &pixmap);
        void remove_user(QString const &name);
};

#endif