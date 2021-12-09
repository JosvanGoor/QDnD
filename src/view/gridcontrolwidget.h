#ifndef VIEW_GRIDCONTROLWIDGET_H
#define VIEW_GRIDCONTROLWIDGET_H

#include <QColorDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QSet>
#include <QVBoxLayout>
#include <QWidget>

#include "colordisplay.h"
#include "gridwidget.h"

class GridControlWidget : public QWidget
{
    Q_OBJECT

    GridWidget *d_grid_widget;

    QGroupBox *d_button_widget;
        QPushButton *d_walk_button;
        QPushButton *d_move_button;
        QPushButton *d_ping_button;
        QPushButton *d_straight_button;
        QPushButton *d_free_button;

    QGroupBox *d_color_widget;
        ColorDisplay *d_color_display;
        QPushButton *d_color_pick;

    QPushButton *d_reset_position;

    QGroupBox *d_line_control;
        QListWidget *d_line_list;
        QPushButton *d_delete_lines;
        QPushButton *d_clear_lines;
        

    public:
        GridControlWidget(GridWidget *grid_widget, QWidget *parent = nullptr);
        ~GridControlWidget();

        void on_reset_position();
        void on_color_selection();
        void on_button_pressed();

        void on_clear_lines();
        void on_delete_lines();
        void on_selection_changed();

        // slots
        void register_line(QString const &name);

    signals:
        void lines_cleared();
        void lines_removed(QVector<QString> const &lines);
        void line_selection_changed(QSet<QString> const &lines);
};

#endif