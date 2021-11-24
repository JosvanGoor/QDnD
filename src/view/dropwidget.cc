#include "dropwidget.h"

////////////////////
//  Constructors  //
////////////////////

DropWidget::DropWidget(QWidget *parent)
:   QLabel(parent)
{
    if (d_accept.isNull())
        d_accept = QPixmap{":data/accept.png"}.scaled(128, 128);
    if (d_deny.isNull())
        d_deny = QPixmap{":data/deny.png"}.scaled(128, 128);

    set_display(QPixmap{":data/neutral.png"});
    d_accept_state = true;

    setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);
}


DropWidget::~DropWidget()
{

}


////////////////////
//     Utility    //
////////////////////

void DropWidget::set_display(QPixmap const &pixmap)
{
    d_display = pixmap;
    setPixmap(pixmap.scaled(128, 128));
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

    if (mime->formats().size() > 1 || !mime->hasImage())
        setPixmap(d_deny);
    else
        setPixmap(d_accept);

    event->acceptProposedAction();
}


void DropWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    std::cout << "dragLeaveEvent\n" << std::flush;
    setPixmap(d_display);
}


void DropWidget::dropEvent(QDropEvent *event)
{
    std::cout << "dropEvent\n" << std::flush;
}