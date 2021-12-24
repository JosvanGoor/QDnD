#ifndef VIEW_ENTITYWIDGET_H
#define VIEW_ENTITYWIDGET_H

#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <QFileDialog>

#include "dropwidget.h"
#include "../utility/enums.h"

class EntityWidget : public QWidget
{
    Q_OBJECT

    QGroupBox *d_entity_widget;
        QListWidget *d_entity_list;
        QPushButton *d_delete_entities;
        QSlider *d_entity_rotation;

    QGroupBox *d_adder_widget;
        DropWidget *d_pixmap_drop;
        QLineEdit *d_entity_name;
        QComboBox *d_entity_size;
        QWidget *d_adder_buttons;
            QPushButton *d_add_entity;
            QPushButton *d_select_file;

    QString d_name_prefix;
    QString d_pixmap_filename;
    uint64_t d_unique_number;

    public:
        explicit EntityWidget(QWidget *parent = nullptr);
        ~EntityWidget();

        void set_name_prefix(QString const &str);

        // slots
        void on_delete_entities();
        void on_add_entity();
        void on_select_file();
        void on_file_dropped(QString const &filename);
        void on_selection_change();

        void on_slider_moved(int value);
        void on_slider_released();

    signals:
        void delete_entities(QVector<QString> const &entities);
        void add_entity(QString const &name, QString const &filename, GridScale scale);
        void entity_selection(QSet<QString> const &names);

        void entity_rotation(int angle);
        void local_entity_rotation(int angle);
};

#endif