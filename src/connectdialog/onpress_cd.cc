#include "connectdialog.h"

void ConnectDialog::on_connect()
{
    accept();
}


void ConnectDialog::on_select()
{
    d_pixmap_path->setText
    (
        QFileDialog::getOpenFileName(this, "Select Image", "", "Any File")
    );
}


void ConnectDialog::on_cancel()
{
    reject();
}