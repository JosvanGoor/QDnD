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

        // mainwindow stuff
        void mainwindow_setup();

        // spellswidget stuff
        void spellswidget_setup();
        void on_spellswidget_selection_change(QString const &name);

        // Chatwidget stuff
        void chatwidget_setup();
        void on_chatwidget_message_entered(QString const &msg);

    signals:
        void debug_output(QString const &message);
        void chatmessage_info(QString const &message);
};

#endif