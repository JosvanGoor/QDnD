#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QHBoxLayout>
#include <QMainWindow>

#include "../centralwidget/centralwidget.h"
#include "../menubar/menubar.h"
#include "../statusbar/statusbar.h"

#include "../clientconnection/clientconnection.h"
#include "../hostconnection/hostconnection.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    MenuBar *d_menu_bar;
    CentralWidget *d_central_widget;
    StatusBar *d_status_bar;

    // connection stuff
    HostConnection *d_server;
    ClientConnection *d_client;

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void connect_connection_buttons();

    signals:
        void debug_output(QString const &msg);

    private slots:
        void on_select_display();

        void on_host_pressed(bool triggered);
        void on_client_pressed(bool triggered);
};

#endif