#ifndef APPLICATIONCONTROL_H
#define APPLICATIONCONTROL_H

#include <QMap>
#include <QObject>

#include "../model/runtimemodel.h"
#include "../view/mainwindow.h"

class ApplicationControl : public QObject
{
    Q_OBJECT

    MainWindow *d_main_window;
    RuntimeModel *d_runtime_model;
    QMap<QString, QString> d_settings;

    public:
        explicit ApplicationControl(QObject *parent = nullptr);
        ~ApplicationControl();

    private:
        void load_settings() noexcept;

        // connect stuff
        void connect_to_mainwindow();

    signals:
        void debug_output(QString const &message);
};

#endif