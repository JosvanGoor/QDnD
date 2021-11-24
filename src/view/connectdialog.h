#ifndef VIEW_CONNECTDIALOG_H
#define VIEW_CONNECTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "dropwidget.h"

class ConnectDialog : public QDialog
{
    Q_OBJECT

    QLineEdit *d_hostname;
    QLineEdit *d_port;
    QLineEdit *d_character_name;
    QPushButton *d_connect;
    QPushButton *d_cancel;
    QPushButton *d_select_avatar;
    QLabel *d_avatar_display;
    QString d_avatar_file;
    DropWidget *d_drop_widget;


    public:
        explicit ConnectDialog(QWidget *parent = nullptr);
        ~ConnectDialog();

        // getters
        QString hostname();
        uint16_t port();
        QString character_name();
        QString avatar_file();
        
        // slots
        void on_connect();
        void on_cancel();
        void on_select_avatar();
};

#endif