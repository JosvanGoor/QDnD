#ifndef MENUBAR_H
#define MENUBAR_H

#include <QAction>
#include <QMenu>
#include <QMenuBar>

class MenuBar : public QMenuBar
{
    Q_OBJECT

    QMenu *d_file;
        QAction *d_new;
        QAction *d_open;
        QAction *d_save;
        QAction *d_save_as;
        QAction *d_quit;

    QMenu *d_connection;
        QAction *d_host;
        QAction *d_connect;
        QAction *d_disconnect;

    QAction *d_debug;

    public:
        explicit MenuBar(QWidget *parent = nullptr);
        ~MenuBar();

        QAction *host_button();
        QAction *client_button();

        bool output_debug_info() const noexcept;
};

#endif