#include "mainwindow.h"

void MainWindow::on_select_display()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select File", "", "Image Files (*.png *.jpg");
    d_central_widget->display_widget()->set_pixmap(QPixmap{filename});
}