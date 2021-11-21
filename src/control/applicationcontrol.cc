#include "applicationcontrol.h"

////////////////////
//  Constructors  //
////////////////////

ApplicationControl::ApplicationControl(QObject *parent)
:   QObject(parent)
{
    d_main_window = new MainWindow;
    d_runtime_model = new RuntimeModel;
    d_connection = nullptr;
    d_identifier = "Dungeon Master";
    
    mainwindow_setup();

    load_settings();
    d_main_window->show();
}


ApplicationControl::~ApplicationControl()
{
    delete d_main_window;
    delete d_runtime_model;
    delete d_connection;
}


////////////////////
//    Settings    //
////////////////////

void ApplicationControl::load_settings() noexcept
{
    debug_output("Started loading settings...");
    debug_output("SYKE persistent settings are not implemented yet");
}


////////////////////
//   ChatWidget   //
////////////////////

void ApplicationControl::chatwidget_setup()
{
    QObject::connect(d_main_window->chat_widget(), &ChatWidget::message_entered, this, &ApplicationControl::on_chatwidget_message_entered);
    QObject::connect(this, &ApplicationControl::chatmessage_info, d_main_window->chat_widget(), &ChatWidget::on_info_message);
}


void ApplicationControl::on_chatwidget_message_entered(QString const &msg)
{
    if (d_connection)
    {
        QJsonDocument doc = chat_message(d_identifier, msg);
        d_connection->send(doc, true);
    }
}

void ApplicationControl::on_chatwidget_user_message(QString const &name, QString const &message)
{
    d_main_window->chat_widget()->on_user_message(name, message);
}


////////////////////
//   Networking   //
////////////////////

bool ApplicationControl::reconnect_confirmation()
{
    if (d_connection)
    {
        QMessageBox confirm{d_main_window};
        confirm.setText("This will disconnect your current connection, are you sure?");
        confirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        if (confirm.exec() == QMessageBox::No)
            return false;
        delete d_connection;
    }
    
    return true;
}


void ApplicationControl::connection_setup()
{
    QObject::connect(d_connection, &ConnectionBase::debug_message, this, &ApplicationControl::debug_output);
    QObject::connect(d_connection, &ConnectionBase::connection_status_update, this, &ApplicationControl::connection_info);
    QObject::connect(d_connection, &ConnectionBase::chat_connection_message, this, &ApplicationControl::chatmessage_info);
    QObject::connect(d_connection, &ConnectionBase::player_disconnected, this, &ApplicationControl::player_disconnected);
    QObject::connect(d_connection, &ConnectionBase::player_connected, this, &ApplicationControl::player_connected);
    QObject::connect(d_connection, &ConnectionBase::chat_message, this, &ApplicationControl::on_chatwidget_user_message);
}


void ApplicationControl::player_connected(QString const &name, QByteArray const &b64_avatar, QColor const &color)
{
    QString avatar_id = d_runtime_model->pixmap_cache().load_from_memory(b64_avatar);
    d_main_window->players_widget()->add_user(name, d_runtime_model->pixmap_cache().get_pixmap(avatar_id), color);
}


void ApplicationControl::player_disconnected(QString const &name)
{
    d_main_window->players_widget()->remove_user(name);
}


////////////////////
//   MainWindow   //
////////////////////

void ApplicationControl::mainwindow_setup()
{
    connect(this, &ApplicationControl::debug_output, d_main_window, &MainWindow::debug_message);

    chatwidget_setup();
    spellswidget_setup();
    statusbar_setup();
    menubar_setup();
}


////////////////////
//    MenuBar     //
////////////////////

void ApplicationControl::menubar_setup()
{
    MenuBar *menubar = d_main_window->menu_bar();

    QObject::connect(menubar->quit(), &QAction::triggered, this, &ApplicationControl::on_menubar_quit);
    QObject::connect(menubar->host(), &QAction::triggered, this, &ApplicationControl::on_menubar_host);
    QObject::connect(menubar->connect(), &QAction::triggered, this, &ApplicationControl::on_menubar_connect);
    QObject::connect(menubar->disconnect(), &QAction::triggered, this, &ApplicationControl::on_menubar_disconnect);
}


void ApplicationControl::on_menubar_quit()
{
    QApplication::exit();
}


void ApplicationControl::on_menubar_host()
{
    if (!reconnect_confirmation())
        return;

    d_connection = new ServerConnection;
    connection_setup();

    reinterpret_cast<ServerConnection*>(d_connection)->start_listening(4144);
}


void ApplicationControl::on_menubar_connect()
{
    if (!reconnect_confirmation())
        return;

    ConnectDialog dialog{d_main_window};
    if (dialog.exec() == QDialog::Rejected)
    {
        debug_output("Connection canceled.");
        return;
    }

    if (dialog.hostname().isEmpty())
    {
        debug_output("Needs Hostname");
        return;
    }
    if (dialog.port() == 0)
    {
        debug_output("Invalid port");
        return;
    }
    if (dialog.character_name().isEmpty())
    {
        debug_output("Needs character name");
        return;
    }

    TransferableImage avatar = d_runtime_model->pixmap_cache().load_from_file(dialog.avatar_file());
    if (avatar.name.isEmpty())
    {
        debug_output("Needs avatar");
        return;
    }

    d_connection = new ClientConnection;
    connection_setup();

    reinterpret_cast<ClientConnection*>(d_connection)->connect(dialog.hostname(), dialog.port());
    d_identifier = dialog.character_name();
    d_connection->send(handshake_message(dialog.character_name(), avatar.b64_data));
}


void ApplicationControl::on_menubar_disconnect()
{
    debug_output("Disconnect not implemented yet.");
}


////////////////////
//  SpellsWidget  //
////////////////////

void ApplicationControl::spellswidget_setup()
{
    SpellsWidget *spells_widget = d_main_window->spells_widget();
    for (auto &spell : d_runtime_model->spells_cache())
        spells_widget->add_spell(spell.name());
    debug_output("Loaded " + QString::number(d_runtime_model->d_spells_cache.size()) + " spells.");
    on_spellswidget_selection_change("Abi-Dalzim's Horrid Wilting"); // HACKY AF

    connect(d_main_window->spells_widget(), &SpellsWidget::selection_changed, this, &ApplicationControl::on_spellswidget_selection_change);
}


void ApplicationControl::on_spellswidget_selection_change(QString const &name)
{
    debug_output("Spell selection changed: " + name);
    auto it = d_runtime_model->spells_cache().find(name);
    if (it != d_runtime_model->spells_cache().end())
    {
        QString description = it.value().format();
        d_main_window->spells_widget()->show_description(description);
    }
}


////////////////////
//   StatusBar    //
////////////////////

void ApplicationControl::statusbar_setup()
{
    StatusBar *status_bar = d_main_window->status_bar();

    QObject::connect(this, &ApplicationControl::connection_info, status_bar, &StatusBar::update_connection_status);
    QObject::connect(this, &ApplicationControl::statusbar_message, status_bar, &StatusBar::status_message);
}