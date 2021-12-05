#ifndef VIEW_GRIDCONTROLWIDGET_H
#define VIEW_GRIDCONTROLWIDGET_H

#include <QColorDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "colordisplay.h"
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

    QGroupBox *d_color_widget;
        ColorDisplay *d_color_display;
        QPushButton *d_color_pick;
        

    public:
        GridControlWidget(GridWidget *grid_widget, QWidget *parent = nullptr);
        ~GridControlWidget();

        void on_color_selection();
        void on_button_pressed();
};

#endif