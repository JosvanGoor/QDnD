#ifndef VIEW_MENUBAR_H
#define VIEW_MENUBAR_H

#include <QAction>
#include <QMenu>
#include <QMenuBar>

class MenuBar : public QMenuBar
{
    Q_OBJECT

    QMenu *d_file;
        QAction *d_save_own_lines;
        QAction *d_save_all_lines;
        QAction *d_load_lines;
        QAction *d_quit;
        QAction *d_update_display;
    QMenu *d_connection;
        QAction *d_host;
        QAction *d_connect;
        QAction *d_disconnect;
        

    public:
        explicit MenuBar(QWidget *parent = nullptr);
        ~MenuBar();

        // getters
        QAction *quit();
        QAction *host();
        QAction *connect();
        QAction *disconnect();
        QAction *update_display();

        QAction *load_lines();
        QAction *save_own_lines();
        QAction *save_all_lines();

};

#endif