#include "applicationcontrol.h"

////////////////////
//  Constructor   //
////////////////////

ApplicationControl::ApplicationControl(QObject *parent)
:   QObject(parent)
{
    d_connection = nullptr;

    create_default_connections();
    load_spells(":/data/spells.json");
    on_spell_selection("Fireball");

    d_main_window.show();
    debug_message("ApplicationControl: setup complete!");
}


ApplicationControl::~ApplicationControl()
{
    delete d_connection;
}


////////////////////
// Initialisation //
////////////////////

void ApplicationControl::create_default_connections()
{
    QObject::connect(this, &ApplicationControl::debug_message, &d_main_window, &MainWindow::debug_message);
    QObject::connect(d_main_window.spells_widget(), &SpellsWidget::selection_changed, this, &ApplicationControl::on_spell_selection);
    QObject::connect(d_main_window.menu_bar()->host(), &QAction::triggered, this, &ApplicationControl::start_hosting);
    QObject::connect(d_main_window.menu_bar()->connect(), &QAction::triggered, this, &ApplicationControl::connect_to_host);
}


void ApplicationControl::load_spells(QString const &filename)
{
    QFile file{filename};
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString text = file.readAll();

    QJsonDocument root = QJsonDocument::fromJson(text.toUtf8());
    QJsonArray sources = root["sources"].toArray();

    for (QJsonValue const &source : sources)
    {
        QString sourcename = source["name"].toString();
        QJsonArray spells = source["spells"].toArray();
        for (QJsonValue const &spell : spells)
        {
            d_main_window.spells_widget()->add_spell(spell["name"].toString());
            d_spells[spell["name"].toString()] = Spell{spell.toObject(), sourcename};
        }
    }

    debug_message("Done loading " + QString::number(d_spells.size()) + " spells.");
}


////////////////////
//   Networking   //    // TODO: verify no connection is open.
////////////////////

bool ApplicationControl::verify_close_connection()
{
    if (!d_connection)
        return true;

    QMessageBox confirm{&d_main_window};
    confirm.setText("This will disconnect your current connection(s), are you sure?");
    confirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (confirm.exec() == QMessageBox::No)
        return false;

    d_connection->disconnect();
    d_connection->deleteLater();
    d_connection = nullptr;
    return true;
}


void ApplicationControl::start_hosting()
{
    if (!verify_close_connection())
        return;
    
    d_connection = new ServerConnection;

    // TODO: connect rest
    QObject::connect(d_connection, &ConnectionBase::debug_message, &d_main_window, &MainWindow::debug_message);
    QObject::connect(d_connection, &ConnectionBase::connection_status, d_main_window.status_bar(), &StatusBar::update_connection_status);
    QObject::connect(d_connection, &ConnectionBase::player_joins, &d_player_control, &PlayerControl::on_player_joins);
    QObject::connect(d_connection, &ConnectionBase::player_leaves, &d_player_control, &PlayerControl::on_player_leaves);
    QObject::connect(&d_player_control, &PlayerControl::trigger_synchronization, this, &ApplicationControl::on_trigger_synchronization);

    d_connection->connect("", 4144);
}


void ApplicationControl::connect_to_host()
{
    if (!verify_close_connection())
        return;

    ConnectDialog dialog{&d_main_window};
    if (dialog.exec() == QDialog::Rejected)
    {
        debug_message("ConnectDialog: Inputs rejected.");
        return;
    }

    d_connection = new ClientConnection;

    QObject::connect(d_connection, &ConnectionBase::debug_message, &d_main_window, &MainWindow::debug_message);
    QObject::connect(d_connection, &ConnectionBase::connection_status, d_main_window.status_bar(), &StatusBar::update_connection_status);
    QObject::connect(d_connection, &ConnectionBase::player_joins, &d_player_control, &PlayerControl::on_player_joins);
    QObject::connect(d_connection, &ConnectionBase::player_leaves, &d_player_control, &PlayerControl::on_player_leaves);

    d_connection->connect(dialog.hostname(), dialog.port());
    
    // TODO: log own identifier
    // TODO: add extra settings to connection dialog
    TransferableImage avatar = d_pixmap_cache.load_from_file(dialog.avatar_file());
    d_connection->send(handshake_message(dialog.character_name(), avatar.b64_data, Qt::black, GridScale::MEDIUM));
}


////////////////////
//  Server Slots  //
////////////////////

void ApplicationControl::on_trigger_synchronization(QString const &id)
{
    debug_message("Sync request for " + id + " triggered.");
}


////////////////////
//     Slots      //
////////////////////

void ApplicationControl::on_pixmap_required(QString const &key)
{
    if (!d_pixmap_cache.has_pixmap(key))
    {
        debug_message("TODO: request pixmap");
    }
}


void ApplicationControl::on_player_connected(Player const &player)
{
    debug_message("New player connected: " + player.identifier());
    // TODO: connect to ui
}


void ApplicationControl::on_player_disconnected(QString const &id)
{
    debug_message("Player disconnected: " + id);
    // TODO: connect to ui
}


void ApplicationControl::on_spell_selection(QString const &name)
{
    debug_message("Spell selection changed to " + name);

    if (auto it = d_spells.find(name); it != d_spells.end())
        d_main_window.spells_widget()->show_description(it.value().format());
}