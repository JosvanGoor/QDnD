#include "dropwidget.h"

////////////////////
//  Constructors  //
////////////////////

DropWidget::DropWidget(QWidget *parent)
:   QLabel(parent)
{
    if (d_accept.isNull())
        d_accept = QPixmap{":data/accept.png"}.scaled(256, 256);
    if (d_deny.isNull())
        d_deny = QPixmap{":data/deny.png"}.scaled(256, 256);


    setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);
    set_preferred_size({256, 256});
    set_display(QPixmap{":data/neutral.png"});
}


DropWidget::~DropWidget()
{

}


////////////////////
//     Utility    //
////////////////////

void DropWidget::set_display(QPixmap const &pixmap)
{
    d_display = pixmap.scaled(d_size);
    setPixmap(pixmap.scaled(d_size));
}


////////////////////
//    Filedrop    //
////////////////////

void DropWidget::dragEnterEvent(QDragEnterEvent *event)
{
    QMimeData const *mime = event->mimeData();

    if (mime->hasUrls())
    {
        QList<QUrl> urls = mime->urls();
        if (urls.size() == 1 && urls[0].scheme() == "file")
        {
            d_file_to_accept = urls[0];
            setPixmap(d_accept);
        }
        else
        {
            d_file_to_accept = QUrl{};
            setPixmap(d_deny);
        }

    }

    event->acceptProposedAction();
}


void DropWidget::dragLeaveEvent([[maybe_unused]] QDragLeaveEvent *event)
{
    setPixmap(d_display);
}


void DropWidget::dropEvent([[maybe_unused]] QDropEvent *event)
{
    QString filename = d_file_to_accept.toLocalFile();
    QPixmap pixmap = squared(QPixmap{filename}.scaled(d_size));

    if (pixmap.isNull())
    {
        d_file_to_accept = "";
        return;
    }

    setPixmap(pixmap);
    emit pixmap_dropped(filename);
}


void DropWidget::set_preferred_size(QSize const &size)
{
    d_size = size;
    setMinimumSize(size);
    setMaximumSize(size);
    set_display(d_display);
}