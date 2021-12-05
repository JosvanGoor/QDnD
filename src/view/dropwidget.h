#ifndef VIEW_DROPWIDGET_H
#define VIEW_DROPWIDGET_H

#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QLabel>

class DropWidget : public QLabel
{
    Q_OBJECT

    QPixmap d_accept;
    QPixmap d_deny;
    QPixmap d_display;
    QUrl d_file_to_accept;
    QSize d_size;

    public:
        explicit DropWidget(QWidget *parent = nullptr);
        ~DropWidget();

        void set_display(QPixmap const &pixmap);

        void dragEnterEvent(QDragEnterEvent *event) override;
        // void dragMoveEvent(QDragMoveEvent *event) override;
        void dragLeaveEvent(QDragLeaveEvent *event) override;
        void dropEvent(QDropEvent *event) override;

        void set_preferred_size(QSize const &size);

    signals:
        void pixmap_dropped(QString const &filename);
};

#endif