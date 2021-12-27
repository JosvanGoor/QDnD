#ifndef VIEW_MAPMANAGERCONTROLWIDGET_H
#define VIEW_MAPMANAGERCONTROLWIDGET_H

#include <QCheckBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "../control/mapmanager.h"

class MapManagerControlWidget : public QWidget
{
    Q_OBJECT

    MapManager *d_manager;

    QListWidget *d_group_list;
    QLineEdit *d_new_group_name;
    QPushButton *d_new_group_button;
    QCheckBox *d_visibility_check;
    QPushButton *d_save_map;
    QPushButton *d_load_map;
    QPushButton *d_insert_map;

    public:
        explicit MapManagerControlWidget(MapManager *manager, QWidget *parent = nullptr);
        ~MapManagerControlWidget();

        // slots
        void on_group_added();
        void on_selection_changed();
        void on_visibility_changed(bool checked);

        void on_save_map();
        void on_load_map();

    signals:
        void group_visibility_changed(QString const &group, VisibilityMode mode);
};

#endif