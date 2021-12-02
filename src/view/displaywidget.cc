#include "displaywidget.h"

////////////////////
//  Constructors  //
////////////////////

DisplayWidget::DisplayWidget(QWidget *parent)
:   QWidget(parent)
{
    d_current_display = QPixmap{":data/display_default.jpg"};
}


DisplayWidget::~DisplayWidget()
{

}


////////////////////
//    Display     //
////////////////////

void DisplayWidget::set_pixmap(QString const &key)
{
    d_pixmap_key = key;
}


void DisplayWidget::set_pixmap(QPixmap const &pixmap)
{
    d_current_display = pixmap;
    d_pixmap_key = "";
    update();
}


void DisplayWidget::paintEvent([[maybe_unused]] QPaintEvent *event)
{
    // first we find the scale of the image vs display size
    float widthscale = qMin(1.0f, float(width()) / d_current_display.width());
    float heightscale = qMin(1.0f, float(height()) / d_current_display.height());
    float scale = qMin(widthscale, heightscale);

    // actual render size
    int im_width = size_t(d_current_display.width() * scale);
    int im_height = size_t(d_current_display.height() * scale);

    // find offsets to center the image
    int x_offset = (width() - im_width) / 2;
    int y_offset = (height() - im_height) / 2;

    QPainter painter{this};
    QRect destination{x_offset, y_offset, im_width, im_height};
    painter.drawPixmap(destination, d_current_display);
}


////////////////////
//    Display     //
////////////////////

void DisplayWidget::pixmap_received(QString const &key, QPixmap const &pixmap)
{
    if (d_pixmap_key.isEmpty())
        return;

    if (d_pixmap_key == key)
        set_pixmap(pixmap);
}