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

    public:
        explicit MenuBar(QWidget *parent = nullptr);
        ~MenuBar();
};

#endif