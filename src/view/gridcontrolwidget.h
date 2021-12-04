#ifndef VIEW_GRIDCONTROLWIDGET_H
#define VIEW_GRIDCONTROLWIDGET_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "gridwidget.h"

class GridControlWidget : public QWidget
{
    GridWidget *d_grid_widget;

    QGroupBox *d_button_widget;
        QPushButton *d_walk_button;
        QPushButton *d_move_button;
        QPushButton *d_ping_button;
        QPushButton *d_straight_button;
        QPushButton *d_free_button;

    public:
        GridControlWidget(GridWidget *grid_widget, QWidget *parent = nullptr);
        ~GridControlWidget();

        void on_button_pressed();
};

#endif