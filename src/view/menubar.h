#ifndef VIEW_MENUBAR_H
#define VIEW_MENUBAR_H

#include <QAction>
#include <QMenu>
#include <QMenuBar>

class MenuBar : public QMenuBar
{
    Q_OBJECT

    QMenu *d_file;
        QAction *d_quit;
    QMenu *d_connection;
        QAction *d_host;
        QAction *d_connect;
        QAction *d_disconnect;

    public:
        explicit MenuBar(QWidget *parent = nullptr);
        ~MenuBar();

        // Host stuff
        void add_server_menus();
        void remove_server_menus();

        // getters
        QAction *quit();
        QAction *host();
        QAction *connect();
        QAction *disconnect();

};

#endif