#ifndef VIEW_ENTITYWIDGET_H
#define VIEW_ENTITYWIDGET_H

#include <QGroupBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "dropwidget.h"

class EntityWidget : public QWidget
{
    Q_OBJECT

    QGroupBox *d_entity_widget;
        QListWidget *d_entity_list;
        QPushButton *d_delete_entities;
        QPushButton *d_clear_entities;

    QGroupBox *d_adder_widget;
        DropWidget *d_pixmap_drop;
        QLineEdit *d_entity_name;
        QWidget *d_adder_buttons;
            QPushButton *d_add_entity;
            QPushButton *d_select_file;

    public:
        explicit EntityWidget(QWidget *parent = nullptr);
        ~EntityWidget();

};

#endif