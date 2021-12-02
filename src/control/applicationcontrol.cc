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
    QObject::connect(d_main_window.menu_bar()->update_display(), &QAction::triggered, this, &ApplicationControl::display_update_clicked);    
    QObject::connect(d_main_window.chat_widget(), &ChatWidget::message_entered, this, &ApplicationControl::chat_entered);

    QObject::connect(&d_player_control, &PlayerControl::pixmap_required, this, &ApplicationControl::on_pixmap_required);
    QObject::connect(&d_player_control, &PlayerControl::player_connected, this, &ApplicationControl::on_player_connected);
    QObject::connect(&d_player_control, &PlayerControl::player_disconnected, this, &ApplicationControl::on_player_disconnected);
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
//   Networking   //
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
    // TODO: set id to "Dungeon Master".
    d_player_control.set_own_identifier("Dungeon Master");
    QObject::connect(&d_player_control, &PlayerControl::trigger_synchronization, this, &ApplicationControl::on_trigger_synchronization);
    QObject::connect(d_connection, &ConnectionBase::pixmap_requested, this, &ApplicationControl::pixmap_requested);
    set_connectionbase_signals();

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
    set_connectionbase_signals();

    d_connection->connect(dialog.hostname(), dialog.port());
    
    // TODO: add extra settings to connection dialog
    d_player_control.set_own_identifier(dialog.character_name());
    TransferableImage avatar = d_pixmap_cache.load_from_file(dialog.avatar_file());
    debug_message("My avatar hash: " + avatar.name);
    d_connection->send(handshake_message(dialog.character_name(), avatar.b64_data, Qt::black, GridScale::MEDIUM));
}


void ApplicationControl::set_connectionbase_signals()
{
    QObject::connect(d_connection, &ConnectionBase::debug_message, &d_main_window, &MainWindow::debug_message);
    QObject::connect(d_connection, &ConnectionBase::connection_status, d_main_window.status_bar(), &StatusBar::update_connection_status);
    QObject::connect(d_connection, &ConnectionBase::player_joins, &d_player_control, &PlayerControl::on_player_joins);
    QObject::connect(d_connection, &ConnectionBase::player_leaves, &d_player_control, &PlayerControl::on_player_leaves);
    QObject::connect(d_connection, &ConnectionBase::pixmap_received, &d_pixmap_cache, &PixmapCache::put_pixmap);
    QObject::connect(d_connection, &ConnectionBase::pixmap_received, d_main_window.players_widget(), &PlayersWidget::pixmap_received);
    QObject::connect(d_connection, &ConnectionBase::pixmap_received, d_main_window.display_widget(), &DisplayWidget::pixmap_received);
    QObject::connect(d_connection, &ConnectionBase::chat_message, d_main_window.chat_widget(), &ChatWidget::on_user_message);
    QObject::connect(d_connection, &ConnectionBase::richtext_message, d_main_window.chat_widget(), &ChatWidget::on_rich_message);
    QObject::connect(d_connection, &ConnectionBase::display_update, this, &ApplicationControl::on_display_update);
}


////////////////////
//     Slots      //
////////////////////

void ApplicationControl::on_pixmap_required(QString const &key)
{
    if (!d_pixmap_cache.has_pixmap(key))
    {
        d_connection->send(pixmap_request_message({key}));
        debug_message("Requested pixmap " + key);
    }
    else
        debug_message("Pixmap " + key + " not requested, found in cache.");
}


void ApplicationControl::on_player_connected(Player const &player)
{
    debug_message("New player connected: " + player.identifier());
    if (d_pixmap_cache.has_pixmap(player.avatar_key()))
        d_main_window.players_widget()->add_user(player.identifier(), d_pixmap_cache.get_pixmap(player.avatar_key()), player.color());
    else 
        d_main_window.players_widget()->add_user(player.identifier(), player.avatar_key(), player.color());

    d_main_window.chat_widget()->on_info_message(player.identifier() + " has joined the game.");
}


void ApplicationControl::on_player_disconnected(QString const &id)
{
    debug_message("Player disconnected: " + id);
    d_main_window.players_widget()->remove_user(id);
    d_main_window.chat_widget()->on_info_message(id + " has left.");
}


void ApplicationControl::on_spell_selection(QString const &name)
{
    debug_message("Spell selection changed to " + name);

    if (auto it = d_spells.find(name); it != d_spells.end())
        d_main_window.spells_widget()->show_description(it.value().format());
}


void ApplicationControl::on_display_update(QString const &key)
{
    if (d_pixmap_cache.has_pixmap(key))
        d_main_window.display_widget()->set_pixmap(d_pixmap_cache.get_pixmap(key));
    else
    {
        d_main_window.display_widget()->set_pixmap(key);
        on_pixmap_required(key);
    }
}

////////////////////
//      Chat      //
////////////////////

void ApplicationControl::chat_entered(QString const &chat)
{
    if (!d_connection)
        return;

    QJsonDocument doc;

    if (chat.startsWith("/roll ") && chat.size() != 6)
    {
        DiceExpressionPtr ptr = DiceParser::parse(chat.mid(6));
        if (ptr == nullptr)
            doc = chat_message(d_player_control.own_identifier(), chat);
        else
        {
            DiceResult result = ptr->evaluate();
            QString rich = result.text + " -> " + QString::number(result.result);
            doc = richtext_message(d_player_control.own_identifier(), rich);    
        }
        
    }
    else
        doc = chat_message(d_player_control.own_identifier(), chat);

    if (d_connection->is_server())
        d_connection->handle_message(doc);
    d_connection->send(doc);
}


////////////////////
//      Menus     //
////////////////////

void ApplicationControl::display_update_clicked()
{
    if (!d_connection || !d_connection->is_server())
    {
        debug_message("Only server may change display.");
        return;
    }
    
    QString file = QFileDialog::getOpenFileName(&d_main_window, "Select an image");

    if (file.isEmpty())
        return;

    TransferableImage image = d_pixmap_cache.load_from_file(file);
    if (image.name.isEmpty())
        return;

    QJsonDocument doc = display_update_message(image.name);
    d_connection->send(doc);
    d_connection->handle_message(doc);
}



////////////////////
//  Server Slots  //
////////////////////

void ApplicationControl::pixmap_requested(QString const &id, QString const &key)
{
    ServerConnection *server = reinterpret_cast<ServerConnection*>(d_connection);

    if (!d_pixmap_cache.has_pixmap(key))
    {
        server->message_to(id, pixmap_not_found_message(key));
        debug_message("Failed to serve pixmap to " + id + ", " + key);
        return;
    }

    TransferableImage transfer = d_pixmap_cache.prepare_for_transfer(key);
    server->queue_message(id, pixmap_transfer_message(transfer.name, transfer.b64_data).toJson());
}


void ApplicationControl::on_trigger_synchronization(QString const &id)
{
    debug_message("Sync request for " + id + " triggered.");
    
    QJsonArray players;
    for (auto &player : d_player_control.players())
        players.push_back(player.serialize());
    
    QJsonObject obj;
    obj["type"] = as_int(MessageType::SYNCHRONIZE);
    obj["players"] = players;
    reinterpret_cast<ServerConnection*>(d_connection)->message_to(id, QJsonDocument{obj});
}
