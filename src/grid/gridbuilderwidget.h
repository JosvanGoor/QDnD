#ifndef GRID_GRIDBUILDERWIDGET_H
#define GRID_GRIDBUILDERWIDGET_H

#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

#include "gridwidget.h"

class GridBuilderWidget : public QWidget
{
    Q_OBJECT

    QGroupBox *d_details_box;
        QRadioButton *d_align_center;
        QRadioButton *d_align_vertical;
        QRadioButton *d_align_horizontal;
        QRadioButton *d_dont_align;
        QPushButton *d_select;

    QPixmap d_mouse_pixmap;
    GridWidget *d_gridwidget;

    public:
        GridBuilderWidget(GridWidget *gridwidget, QWidget *parent = nullptr);
        ~GridBuilderWidget();


        void on_select();
        void on_toggled(bool checked);
};

#endif