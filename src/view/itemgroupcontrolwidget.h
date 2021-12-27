#ifndef VIEW_ITEMGROUPCONTROLWIDGET_H
#define VIEW_ITEMGROUPCONTROLWIDGET_H

#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

#include "dropwidget.h"
#include "gridwidget.h"
#include "../control/mapmanager.h"
#include "../utility/enums.h"

class ItemGroupControlWidget : public QWidget
{
    Q_OBJECT

    int d_selection;
    GridWidget *d_grid;
    MapManager *d_manager;
    QString d_pixmap_filename;
    MouseMode d_current_mode;
    
    QLabel *d_group_name;
    QGroupBox *d_mouse_mode;
        QPushButton *d_placement_mode;
        QPushButton *d_selection_mode;
        QCheckBox *d_snap_horizontal_check;
        QCheckBox *d_snap_vertical_check;
        QCheckBox *d_snap_xoffset_check;
        QCheckBox *d_snap_yoffset_check;
    QGroupBox *d_current_item;
        DropWidget *d_pixmap_selection;
        QLineEdit *d_xpos_edit;
        QLineEdit *d_ypos_edit;
        QSlider *d_rotation_slider;
        QLabel *d_rotation_label;
        QComboBox *d_scale_selection;
        QPushButton *d_remove_item;

    public:
        explicit ItemGroupControlWidget(GridWidget *d_grid, MapManager *manager, QWidget *parent = nullptr);
        ~ItemGroupControlWidget();

        // utility
        void reset_mouse_mode();

        // slots
        void on_snap_changed(bool checked);
        void on_mouse_mode_changed();
        void on_pixmap_dropped(QString const &filename);
        void on_rotation_changed(int value);
        void on_scale_changed(int index);

        void on_remove();
        void on_group_selection_changed();
        void on_grid_item_click(QPoint const &position);

        void clear_selection();
        void on_grid_selection_click(QPoint const &position);
        void on_grid_selection_rclick();

    signals:
        void debug_message(QString const &message);
        void place_grid_item(QString const &filename, QPoint position, int rotation, GridScale scale, VisibilityMode mode);
        void remove_grid_item(int index);
};

#endif