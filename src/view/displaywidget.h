#ifndef VIEW_DISPLAYWIDGET_H
#define VIEW_DISPLAYWIDGET_H

#include <QPainter>
#include <QPixmap>
#include <QWidget>

class DisplayWidget : public QWidget
{
    Q_OBJECT

    QPixmap d_current_display;

    public:
        explicit DisplayWidget(QWidget *parent = nullptr);
        ~DisplayWidget();

        void set_pixmap(QPixmap const &pixmap);
        void paintEvent(QPaintEvent *event) override;
};

#endif