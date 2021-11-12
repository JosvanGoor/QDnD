#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QGroupBox>
#include <QLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <iostream>

class DisplayWidget : public QWidget
{
    Q_OBJECT

    QPixmap d_current_display;

    public:
        explicit DisplayWidget(QWidget *parent = nullptr);
        ~DisplayWidget();

        void set_pixmap(QPixmap &&pixmap);
        void paintEvent(QPaintEvent *event) override;
};


class DisplayControlWidget : public QGroupBox
{
    Q_OBJECT

    QPushButton *d_select_button;

    public:
        explicit DisplayControlWidget(QWidget *parent = nullptr);
        ~DisplayControlWidget();

        QPushButton *select_button();
};

#endif