#ifndef VIEW_PLAYERSWIDGET_H
#define VIEW_PLAYERSWIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class PlayersWidget : public QWidget
{
    Q_OBJECT

    QScrollArea *d_scroll_area;
    QMap<QString, QWidget*> d_portraits;

    public:
        explicit PlayersWidget(QWidget *parent = nullptr);
        ~PlayersWidget();

        void add_user(QString const &name, QPixmap const &pixmap, QColor const &color);
        void remove_user(QString const &name);
};  

#endif