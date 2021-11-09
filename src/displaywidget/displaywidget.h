#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QWidget>

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

#endif