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

    set_display(QPixmap{":data/neutral.png"});

    setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);
    setMinimumSize(256, 256);
    setMaximumSize(256, 256);
}


DropWidget::~DropWidget()
{

}


////////////////////
//     Utility    //
////////////////////

void DropWidget::set_display(QPixmap const &pixmap)
{
    d_display = pixmap.scaled(256, 256);
    setPixmap(pixmap.scaled(256, 256));
}


////////////////////
//    Filedrop    //
////////////////////
#include <iostream> // TODO: remove

void DropWidget::dragEnterEvent(QDragEnterEvent *event)
{
    QMimeData const *mime = event->mimeData();

    for (auto &format : mime->formats())
    {
        std::cout << format.toStdString() << "\n" << std::flush;
    }

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


void DropWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    setPixmap(d_display);
}


void DropWidget::dropEvent(QDropEvent *event)
{
    QString filename = d_file_to_accept.toLocalFile();
    QPixmap pixmap = QPixmap{filename}.scaled(256, 256);

    if (pixmap.isNull())
    {
        d_file_to_accept = "";
        return;
    }

    setPixmap(pixmap);
    emit pixmap_dropped(filename);
}