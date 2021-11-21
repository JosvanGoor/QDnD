#ifndef VIEW_DISPLAYWIDGET_H
#define VIEW_DISPLAYWIDGET_H

#include <QPainter>
#include <QPixmap>
#include <QWidget>

class DisplayWidget : public QWidget
{
    Q_OBJECT

    QPixmap d_current_display;
    QString d_incoming_pixmap_name;

    public:
        explicit DisplayWidget(QWidget *parent = nullptr);
        ~DisplayWidget();

        bool waiting_for_pixmap(QString const &id);
        void set_incoming_pixmap(QString const &id);

        void set_pixmap(QPixmap const &pixmap);
        void paintEvent(QPaintEvent *event) override;
};

#endif