#include "mainwindow.h"

void MainWindow::on_select_display()
{
    if (d_server == nullptr)
        return;
        
    QString filename = QFileDialog::getOpenFileName(this, "Select File", "", "Image Files (*.png *.jpg");
    d_central_widget->display_widget()->set_pixmap(QPixmap{filename});

    QString imdata = read_file_conditionally_b64(filename);
    if (imdata.isEmpty())
        return;

    QJsonObject obj;
    obj["type"] = "DISPLAY_UPDATE";
    obj["name"] = filename;
    obj["data"] = imdata;
    QJsonDocument doc{obj};

    d_server->dispatch(doc);
}