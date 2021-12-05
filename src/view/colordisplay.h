#ifndef VIEW_COLORDISPLAY_H
#define VIEW_COLORDISPLAY_H

#include <QColor>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

class ColorDisplay : public QWidget
{
    QColor d_color;

    public:
        ColorDisplay(QColor color, QWidget *parent = nullptr);
        ~ColorDisplay();

        QColor color();
        void set_color(QColor color);

        void paintEvent(QPaintEvent *event) override;
};

#endif