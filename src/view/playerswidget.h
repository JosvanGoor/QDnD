#ifndef VIEW_PLAYERSWIDGET_H
#define VIEW_PLAYERSWIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

struct Portrait
{
    QString avatar_key;
    QWidget *widget_ptr;
    QLabel *icon_label;
};

class PlayersWidget : public QWidget
{
    Q_OBJECT

    QScrollArea *d_scroll_area;
    QMap<QString, Portrait> d_portraits;

    public:
        explicit PlayersWidget(QWidget *parent = nullptr);
        ~PlayersWidget();

        void add_user(QString const &name, QPixmap const &pixmap, QColor const &color);
        void add_user(QString const &name, QString const &key, QColor const &color);
        void remove_user(QString const &name);

        // slot
        void pixmap_received(QString const &key, QPixmap const &pixmap);
};  

#endif