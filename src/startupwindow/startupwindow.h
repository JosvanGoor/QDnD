#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <QWidget>

class StartupWindow : public QMainWindow
{
    Q_OBJECT

    QWidget *d_central_widget;
        QGroupBox *d_new_session_widget;
            QPushButton *d_new_session_button;
        QGroupBox *d_load_session_widget;
            QPushButton *d_load_session_button;
            QLineEdit *d_load_session_filename;
            QLineEdit *d_load_session_portnr;
        QGroupBox *d_join_session_widget;
            QPushButton *d_join_session_button;
            QLineEdit *d_join_session_address;
            QLineEdit *d_join_session_name;

    public:
        explicit StartupWindow(QWidget *parent = nullptr);
        ~StartupWindow();
};

#endif