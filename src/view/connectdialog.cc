#include "connectdialog.h"

////////////////////
//  Constructors  //
////////////////////

ConnectDialog::ConnectDialog(QWidget *parent)
:   QDialog(parent)
{
    QWidget *form = new QWidget;
    QFormLayout *form_layout = new QFormLayout;
    form_layout->addRow("Hostname", d_hostname = new QLineEdit);
    form_layout->addRow("Port", d_port = new QLineEdit);
    form_layout->addRow("Data Port", d_data_port = new QLineEdit);
    form_layout->addRow("Character Name", d_character_name = new QLineEdit);
    form->setLayout(form_layout);

    QWidget *buttons = new QWidget;
    buttons->setLayout(new QHBoxLayout);
    buttons->layout()->addWidget(d_connect = new QPushButton{"Connect"});
    buttons->layout()->addWidget(d_cancel = new QPushButton{"Cancel"});
    buttons->layout()->addWidget(d_select_avatar = new QPushButton{"Select Avatar"});

    QGroupBox *group_box = new QGroupBox{"Avatar"};
    group_box->setLayout(new QHBoxLayout);
    group_box->layout()->setAlignment(Qt::AlignCenter);
    group_box->layout()->addWidget(d_drop_widget = new DropWidget);
    QPixmap pixmap{":data/default_avatar.png"};
    d_drop_widget->set_display(pixmap);

    d_hostname->setText("jbvg.nl");
    d_port->setText("4144");
    d_data_port->setText("41201");
    d_data_port->setEnabled(false);

    setLayout(new QVBoxLayout);
    layout()->addWidget(form);
    layout()->addWidget(buttons);
    layout()->addWidget(group_box);
    
    layout()->setAlignment(Qt::AlignHCenter);
    d_avatar_file = ":data/default_avatar.png";
    QObject::connect(d_connect, &QPushButton::pressed, this, &ConnectDialog::on_connect);
    QObject::connect(d_cancel, &QPushButton::pressed, this, &ConnectDialog::on_cancel);
    QObject::connect(d_select_avatar, &QPushButton::pressed, this, &ConnectDialog::on_select_avatar);
    QObject::connect(d_drop_widget, &DropWidget::pixmap_dropped, this, &ConnectDialog::on_avatar_dragged);
}


ConnectDialog::~ConnectDialog()
{

}


////////////////////
//    Getters     //
////////////////////

QString ConnectDialog::hostname()
{
    return d_hostname->text();
}


uint16_t ConnectDialog::port()
{
    return d_port->text().toUShort();
}


QString ConnectDialog::character_name()
{
    return d_character_name->text();
}


QString ConnectDialog::avatar_file()
{
    return d_avatar_file;
}



////////////////////
//     Slots      //
////////////////////

void ConnectDialog::on_connect()
{
    accept();
}


void ConnectDialog::on_cancel()
{
    reject();
}


void ConnectDialog::on_select_avatar()
{
    d_avatar_file = QFileDialog::getOpenFileName(this, "Select Image File", "", "");
    
    QFile file{d_avatar_file};
    file.open(QIODevice::ReadOnly);
    QByteArray arr = file.readAll();
    
    QPixmap new_avatar;
    new_avatar.loadFromData(arr);
    d_drop_widget->setPixmap(new_avatar.scaled(d_drop_widget->size()));
}


void ConnectDialog::on_avatar_dragged(QString const &file)
{
    d_avatar_file = file;
}