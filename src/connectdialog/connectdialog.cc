#include "connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent)
:   QDialog(parent)
{
    QFormLayout *layout = new QFormLayout;
    
    d_pixmap_selector = new QWidget;
    d_pixmap_selector->setLayout(new QHBoxLayout);
    d_pixmap_selector->layout()->addWidget(d_pixmap_path = new QLineEdit);
    d_pixmap_selector->layout()->addWidget(d_select_path = new QPushButton{"Select"});
    
    layout->addRow("Hostname", d_hostname = new QLineEdit{"jbvg.nl"});
    layout->addRow("Port", d_port = new QLineEdit("4144"));
    layout->addRow("Character Name", d_character_name = new QLineEdit);
    layout->addRow("Avatar file", d_pixmap_selector);
    layout->addRow("", d_connect = new QPushButton{"Connect"});
    layout->addRow("", d_cancel = new QPushButton{"Cancel"});

    d_hostname->setEnabled(false);
    d_port->setEnabled(false);

    setLayout(layout);
    setModal(true);

    QObject::connect
    (
        d_select_path,
        &QPushButton::pressed,
        this,
        &ConnectDialog::on_select
    );

    QObject::connect
    (
        d_connect,
        &QPushButton::pressed,
        this,
        &ConnectDialog::on_connect
    );

    QObject::connect
    (
        d_cancel,
        &QPushButton::pressed,
        this,
        &ConnectDialog::on_cancel
    );
}


ConnectDialog::~ConnectDialog()
{

}