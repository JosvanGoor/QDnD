#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>

struct ConnectDialogInfo
{
    QString hostname;
    uint16_t port;
    QString character_name;
    QString pixmap_path;
};

class ConnectDialog : public QDialog
{
    Q_OBJECT

    QLineEdit *d_hostname;
    QLineEdit *d_port;
    QLineEdit *d_character_name;
    QWidget *d_pixmap_selector;
        QLineEdit *d_pixmap_path;
        QPushButton *d_select_path;
    QPushButton *d_connect;
    QPushButton *d_cancel;

    public:
        explicit ConnectDialog(QWidget *parent = nullptr);
        ~ConnectDialog();

        ConnectDialogInfo get_entries();

        void on_connect();
        void on_select();
        void on_cancel();


};

#endif