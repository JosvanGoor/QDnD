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
    QObject::connect(this, &ApplicationControl::update_grid, d_main_window.grid_widget(), &GridWidget::request_render_update);
    QObject::connect(d_main_window.spells_widget(), &SpellsWidget::selection_changed, this, &ApplicationControl::on_spell_selection);
    QObject::connect(d_main_window.menu_bar()->host(), &QAction::triggered, this, &ApplicationControl::start_hosting);
    QObject::connect(d_main_window.menu_bar()->connect(), &QAction::triggered, this, &ApplicationControl::connect_to_host);
    QObject::connect(d_main_window.menu_bar()->update_display(), &QAction::triggered, this, &ApplicationControl::display_update_clicked);
    QObject::connect(d_main_window.menu_bar()->load_lines(), &QAction::triggered, this, &ApplicationControl::load_lines);
    QObject::connect(d_main_window.menu_bar()->save_own_lines(), &QAction::triggered, this, &ApplicationControl::save_own_lines);
    QObject::connect(d_main_window.menu_bar()->save_all_lines(), &QAction::triggered, this, &ApplicationControl::save_all_lines);
    QObject::connect(d_main_window.chat_widget(), &ChatWidget::message_entered, this, &ApplicationControl::chat_entered);

    QObject::connect(&d_entity_manager, &EntityManager::update_grid, d_main_window.grid_widget(), &GridWidget::request_render_update);
    QObject::connect(&d_entity_manager, &EntityManager::pixmap_required, this, &ApplicationControl::on_pixmap_required);

    QObject::connect(&d_player_control, &PlayerControl::pixmap_required, this, &ApplicationControl::on_pixmap_required);
    QObject::connect(&d_player_control, &PlayerControl::player_connected, this, &ApplicationControl::on_player_connected);
    QObject::connect(&d_player_control, &PlayerControl::player_disconnected, this, &ApplicationControl::on_player_disconnected);
    QObject::connect(&d_player_control, &PlayerControl::debug_message, &d_main_window, &MainWindow::debug_message);
    QObject::connect(&d_player_control, &PlayerControl::update_grid, d_main_window.grid_widget(), &GridWidget::request_render_update);

    QObject::connect(d_main_window.entity_widget(), &EntityWidget::add_entity, this, &ApplicationControl::on_entity_added);
    QObject::connect(d_main_window.entity_widget(), &EntityWidget::delete_entities, this, &ApplicationControl::on_entities_removed);
    QObject::connect(d_main_window.entity_widget(), &EntityWidget::entity_selection, this, &ApplicationControl::on_entities_selection);
    QObject::connect(d_main_window.entity_widget(), &EntityWidget::local_entity_rotation, this, &ApplicationControl::on_entity_local_rotation);
    QObject::connect(d_main_window.entity_widget(), &EntityWidget::entity_rotation, this, &ApplicationControl::on_entity_rotation);

    QObject::connect(&d_map_manager, &MapManager::pixmap_required, this, &ApplicationControl::on_pixmap_required);
    QObject::connect(&d_map_manager, &MapManager::update_grid, this, &ApplicationControl::update_grid);
    QObject::connect(&d_map_manager, &MapManager::preload_pixmap, this, &ApplicationControl::load_pixmap_file);

    QObject::connect(d_main_window.grid_control_widget(), &GridControlWidget::lines_cleared, this, &ApplicationControl::on_grid_delete_all_lines);
    QObject::connect(d_main_window.grid_control_widget(), &GridControlWidget::lines_removed, this, &ApplicationControl::on_grid_delete_lines);
    QObject::connect(d_main_window.grid_control_widget(), &GridControlWidget::line_selection_changed, this, &ApplicationControl::on_grid_line_selection);
    QObject::connect(d_main_window.grid_widget(), &GridWidget::debug_message, &d_main_window, &MainWindow::debug_message);
    QObject::connect(d_main_window.grid_widget(), &GridWidget::paint_ground_layer, this, &ApplicationControl::on_paint_ground_layer);
    QObject::connect(d_main_window.grid_widget(), &GridWidget::paint_player_layer, this, &ApplicationControl::on_paint_player_layer);
    QObject::connect(d_main_window.grid_widget(), &GridWidget::paint_entity_layer, this, &ApplicationControl::on_paint_entity_layer);
    QObject::connect(d_main_window.grid_widget(), &GridWidget::paint_mouse_layer, this, &ApplicationControl::on_paint_mouse_layer);
    QObject::connect(d_main_window.grid_widget(), &GridWidget::grid_player_move, this, &ApplicationControl::on_grid_player_move);
    QObject::connect(d_main_window.grid_widget(), &GridWidget::grid_line_drawn, this, &ApplicationControl::on_grid_line_drawn);
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


void ApplicationControl::reset()
{
    d_player_control.clear();
    d_pixmap_cache.clear();
    d_entity_manager.clear();
    d_main_window.entity_widget()->set_name_prefix("");
    d_main_window.unload_editor();
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

    reset();
    d_connection->disconnect();
    d_connection->deleteLater();
    QObject::disconnect(&d_player_control, &PlayerControl::trigger_synchronization, this, &ApplicationControl::on_trigger_synchronization);
    QObject::disconnect(d_connection, &ConnectionBase::pixmap_requested, this, &ApplicationControl::pixmap_requested);
    QObject::disconnect(d_main_window.entity_widget(), &EntityWidget::add_entity, this, &ApplicationControl::on_entity_added);
    
    d_connection = nullptr;
    return true;
}


void ApplicationControl::start_hosting()
{
    if (!verify_close_connection())
        return;
    
    d_connection = new ServerConnection;

    TransferableImage dm_ava = d_pixmap_cache.load_from_file(":/data/dmpic.png");
    d_player_control.create_dungeon_master(dm_ava.name);
    d_main_window.load_editor(&d_map_manager);
    
    QObject::connect(&d_player_control, &PlayerControl::trigger_synchronization, this, &ApplicationControl::on_trigger_synchronization);
    QObject::connect(d_connection, &ConnectionBase::pixmap_requested, this, &ApplicationControl::pixmap_requested);

    QObject::connect(d_main_window.item_group_control(), &ItemGroupControlWidget::place_grid_item, this, &ApplicationControl::on_grid_item_placed);
    QObject::connect(d_main_window.map_manager(), &MapManagerControlWidget::group_visibility_changed, this, &ApplicationControl::on_grid_group_visibility_set);

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
    d_player_control.set_own_identifier(dialog.character_name());
    d_main_window.entity_widget()->set_name_prefix(d_player_control.own_identifier());
    TransferableImage avatar = d_pixmap_cache.load_from_file(dialog.avatar_file());
    debug_message("My avatar hash: " + avatar.name);
    d_connection->send(handshake_message(dialog.character_name(), avatar.b64_data, Qt::black, GridScale::MEDIUM));
}


void ApplicationControl::set_connectionbase_signals()
{
    QObject::connect(d_connection, &ConnectionBase::pixmap_received, &d_pixmap_cache, &PixmapCache::put_pixmap);
    
    QObject::connect(d_connection, &ConnectionBase::debug_message, &d_main_window, &MainWindow::debug_message);
    QObject::connect(d_connection, &ConnectionBase::connection_status, d_main_window.status_bar(), &StatusBar::update_connection_status);
    QObject::connect(d_connection, &ConnectionBase::pixmap_received, d_main_window.display_widget(), &DisplayWidget::pixmap_received);
    QObject::connect(d_connection, &ConnectionBase::chat_message, d_main_window.chat_widget(), &ChatWidget::on_user_message);
    QObject::connect(d_connection, &ConnectionBase::richtext_message, d_main_window.chat_widget(), &ChatWidget::on_rich_message);
    QObject::connect(d_connection, &ConnectionBase::pixmap_received, d_main_window.players_widget(), &PlayersWidget::pixmap_received);
    
    QObject::connect(d_connection, &ConnectionBase::player_leaves, &d_player_control, &PlayerControl::on_player_leaves);
    QObject::connect(d_connection, &ConnectionBase::player_joins, &d_player_control, &PlayerControl::on_player_joins);
    QObject::connect(d_connection, &ConnectionBase::player_moved, &d_player_control, &PlayerControl::on_player_moves);
    QObject::connect(d_connection, &ConnectionBase::line_received, &d_player_control, &PlayerControl::on_line_received);
    QObject::connect(d_connection, &ConnectionBase::lines_removed, &d_player_control, &PlayerControl::on_lines_removed);
    QObject::connect(d_connection, &ConnectionBase::lines_cleared, &d_player_control, &PlayerControl::on_lines_cleared);
    
    QObject::connect(d_connection, &ConnectionBase::line_sync, this, &ApplicationControl::on_line_sync);
    QObject::connect(d_connection, &ConnectionBase::display_update, this, &ApplicationControl::on_display_update);
    QObject::connect(d_connection, &ConnectionBase::pixmap_received, this, &ApplicationControl::on_pixmap_received);
    
    QObject::connect(d_connection, &ConnectionBase::entity_added, &d_entity_manager, &EntityManager::on_entity_added);
    QObject::connect(d_connection, &ConnectionBase::entities_removed, &d_entity_manager, &EntityManager::on_entities_removed);
    QObject::connect(d_connection, &ConnectionBase::entities_cleared, &d_entity_manager, &EntityManager::on_entities_cleared);
    QObject::connect(d_connection, &ConnectionBase::entities_moved, &d_entity_manager, &EntityManager::on_entities_moved);
    QObject::connect(d_connection, &ConnectionBase::entities_rotated, &d_entity_manager, &EntityManager::on_entities_rotated);
    QObject::connect(d_connection, &ConnectionBase::synchronize_entities, &d_entity_manager, &EntityManager::on_entities_synchronized);

    QObject::connect(d_connection, &ConnectionBase::clear_grid_groups, &d_map_manager, &MapManager::clear_map);
    QObject::connect(d_connection, &ConnectionBase::grid_item_added, &d_map_manager, &MapManager::on_grid_item_added);
    QObject::connect(d_connection, &ConnectionBase::grid_group_visibility, &d_map_manager, &MapManager::on_group_visibility);
    QObject::connect(d_connection, &ConnectionBase::synchronize_grid_group, &d_map_manager, &MapManager::on_synchronize_grid_group);
}


////////////////////
//     Slots      //
////////////////////

void ApplicationControl::on_pixmap_required(QString const &key)
{
    if (!d_pixmap_cache.has_pixmap(key))
    {
        if (auto it = d_pixmap_requests.find(key); it != d_pixmap_requests.end())
            return;
        
        d_pixmap_requests.insert(key);
        d_connection->send(pixmap_request_message({key}));
    }
}


void ApplicationControl::on_player_connected(Player const &player)
{
    debug_message("New player connected: " + player.identifier());
    if (d_pixmap_cache.has_pixmap(player.avatar_key()))
        d_main_window.players_widget()->add_user(player.identifier(), d_pixmap_cache.get_pixmap(player.avatar_key()), player.color());
    else 
        d_main_window.players_widget()->add_user(player.identifier(), player.avatar_key(), player.color());

    d_main_window.chat_widget()->on_info_message(player.identifier() + " has joined the game.");
    emit update_grid();
}


void ApplicationControl::on_player_disconnected(QString const &id)
{
    debug_message("Player disconnected: " + id);
    d_main_window.players_widget()->remove_user(id);
    d_main_window.chat_widget()->on_info_message(id + " has left.");
    emit update_grid();
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


void ApplicationControl::on_line_sync(QJsonObject const &obj)
{
    Player &player = d_player_control.player(obj["id"].toString());

    QJsonArray line_objects = obj["lines"].toArray();
    for (auto object : line_objects)
    {
        QString name = object.toObject()["name"].toString();
        QColor color = static_cast<unsigned int>(object.toObject()["color"].toInt());
        QJsonArray line = object.toObject()["points"].toArray();
        QVector<QLine> lines;
        for (int idx = 0; idx < (line.size() - 1); ++idx)
        {
            QPoint p1 = {line[idx].toObject()["x"].toInt(), line[idx].toObject()["y"].toInt()};
            QPoint p2 = {line[idx + 1].toObject()["x"].toInt(), line[idx + 1].toObject()["y"].toInt()};
            lines.push_back({p1, p2});
        }

        player.add_line(name, {color, lines});
    }

    update_grid();
}

void ApplicationControl::on_pixmap_received(QString const &key, [[maybe_unused]] QPixmap const &pixmap)
{
    d_pixmap_requests.remove(key);
    update_grid();
}


////////////////////
//      Grid      //
////////////////////

void ApplicationControl::on_grid_line_drawn(QVector<QLine> const &lines, QColor const &color)
{
    if (!d_connection)
        return;

    QString id = d_player_control.own_identifier();
    QString name = d_player_control.unique_name();
    d_connection->send(line_drawn_message(id, name, lines, color));
    d_main_window.grid_control_widget()->register_line(name);
}


void ApplicationControl::on_grid_player_move(QPoint const &point)
{
    if (!d_connection)
        return;

    if (!d_entity_selection.isEmpty())
        d_connection->send(entities_moved_message(d_entity_selection, point));
    else if (!d_connection->is_server())
        d_connection->send(player_move_message(d_player_control.own_identifier(), point));
}


void ApplicationControl::on_grid_delete_lines(QVector<QString> const &lines)
{
    if (!d_connection)
        return;
    d_connection->send(lines_removal_message(d_player_control.own_identifier(), lines));
}


void ApplicationControl::on_grid_line_selection(QSet<QString> const &lines)
{
    d_line_selection = lines;
    update_grid();
}


void ApplicationControl::on_grid_delete_all_lines()
{
    if (!d_connection)
        return;

    QMessageBox confirm{&d_main_window};
    confirm.setText("Are you sure you want to clear all your lines?");
    confirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (confirm.exec() == QMessageBox::No)
        return;

    d_connection->send(lines_cleared_message(d_player_control.own_identifier()));
}


////////////////////
//     Entity     //
////////////////////

void ApplicationControl::on_entity_added(QString const &name, QString const &filename, GridScale scale)
{
    if (!d_connection)
        return;

    TransferableImage avatar = d_pixmap_cache.load_from_file(filename);

    if (d_connection->is_server())
        d_connection->send(entity_added_message(name, avatar.name, {-1'000'000, -1'000'000}, scale));
    else
        d_connection->send(player_entity_added_message(name, avatar.b64_data, {0, 0}, scale));
}


void ApplicationControl::on_entities_removed(QVector<QString> const &entities)
{
    d_connection->send(entities_removed_message(entities));
}


void ApplicationControl::on_entities_selection(QSet<QString> const &names)
{
    d_entity_selection = names;
    update_grid();
}


void ApplicationControl::on_entity_local_rotation(int angle)
{
    d_local_angle = angle;
    update_grid();
}


void ApplicationControl::on_entity_rotation(int angle)
{
    if (!d_connection)
        return;

    d_connection->send(entities_rotated_message(d_entity_selection, angle));
}


////////////////////
//  Map Editing   //
////////////////////

void ApplicationControl::on_grid_item_placed(QString const &filename, QPoint position, int rotation, GridScale scale, VisibilityMode mode)
{
    if (!d_connection)
        return;

    // this is stupid
    // TODO: make this better.
    TransferableImage image = d_pixmap_cache.load_from_file(filename);
    GridItem item;
    item.pixmap_code = image.name;
    item.position = position;
    item.rotation = rotation;
    item.scale = scale;
    item.visibility = mode;
    
    d_map_manager.selected_group().list_filename(image.name, filename);
    d_connection->send(grid_item_added_message(d_map_manager.selected_group_name(), item));
}


void ApplicationControl::on_grid_group_visibility_set(QString const &group, VisibilityMode mode)
{
    if (!d_connection)
        return;
    debug_message("on_grid_group_visibility_set");
    d_connection->send(grid_group_visibility_message(group, mode));
}

////////////////////
//      Misc      //
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

    d_connection->send(doc);
}


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
}


////////////////////
//  Server Slots  //
////////////////////

void ApplicationControl::load_pixmap_file(QString const &filename, QString const &key)
{
    QPixmap pixmap{filename};
    d_pixmap_cache.put_pixmap(key, pixmap);
}


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

    for (auto &player : d_player_control.players())
    {
        if (!player.lines().isEmpty())
            reinterpret_cast<ServerConnection*>(d_connection)->queue_message(id, synchronize_lines_message(player.identifier(), player.lines()).toJson(QJsonDocument::Compact));
    }

    if (!d_entity_manager.entities().isEmpty())
        reinterpret_cast<ServerConnection*>(d_connection)->queue_message(id, synchronize_entities_message(d_entity_manager.entities()).toJson(QJsonDocument::Compact));

    on_map_synchronization(id);
}


void ApplicationControl::on_map_synchronization(QString const &id)
{
    reinterpret_cast<ServerConnection*>(d_connection)->message_to(id, grid_groups_cleared_message().toJson(QJsonDocument::Compact));
    for (auto const &group : d_map_manager.grid_groups())
        reinterpret_cast<ServerConnection*>(d_connection)->queue_message(id, synchronize_grid_group_message(group).toJson(QJsonDocument::Compact));
}


////////////////////
//  Save & Load   //
////////////////////

void ApplicationControl::save_own_lines()
{
    QString filename = QFileDialog::getSaveFileName(&d_main_window, "Select a Save Location");
    if (filename.isEmpty())
    {
        debug_message("Nothing Saved.");
        return;
    }

    Player &player = d_player_control.own_player();
    QJsonArray lines;
    for (auto it = player.lines().begin(); it != player.lines().end(); ++it)
        lines.append(drawline_to_json(it.key(), it.value()));

    QJsonObject obj;
    obj["type"] = "LineStorage_QDND_1.0";
    obj["lines"] = lines;
    QJsonDocument document{obj};

    QFile file{filename};
    file.open(QIODevice::WriteOnly);
    file.write(document.toJson(QJsonDocument::Compact));
    file.close();
}


void ApplicationControl::save_all_lines()
{
    QString filename = QFileDialog::getSaveFileName(&d_main_window, "Select a Save Location");
    if (filename.isEmpty())
    {
        debug_message("Nothing Saved.");
        return;
    }

    QJsonArray lines;
    for (auto &player : d_player_control.players())
    {
        for (auto it = player.lines().begin(); it != player.lines().end(); ++it)
            lines.append(drawline_to_json(it.key(), it.value()));
    }
    
    QJsonObject obj;
    obj["type"] = "LineStorage_QDND_1.0";
    obj["lines"] = lines;
    QJsonDocument document{obj};

    QFile file{filename};
    file.open(QIODevice::WriteOnly);
    file.write(document.toJson(QJsonDocument::Compact));
    file.close();
}


void ApplicationControl::load_lines()
{
    if (!d_connection)
        return;
        
    QString filename = QFileDialog::getOpenFileName(&d_main_window, "Select Line File");
    if (filename.isEmpty())
        return;

    QFile file{filename};
    file.open(QIODevice::ReadOnly);
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());

    if (document["type"].toString() != "LineStorage_QDND_1.0")
    {
        debug_message("Invalid file!");
        return;
    }

    QMap<QString, DrawLine> line_cache;
    QJsonArray lines = document["lines"].toArray();
    for (auto line : lines)
    {
        auto parsed = json_to_drawline(line.toObject());
        line_cache[parsed.first + "!"] = parsed.second;
        d_main_window.grid_control_widget()->register_line(parsed.first + "!");
    }

    d_connection->send(synchronize_lines_message(d_player_control.own_identifier(), line_cache));
}

////////////////////
//    Painting    //
////////////////////

void ApplicationControl::on_paint_ground_layer(QPainter &painter, QSize size, QPoint offset, [[maybe_unused]] QPoint mouse)
{
    for (GridItemGroup const &group : d_map_manager.grid_groups())
    {
        if (group.visibility_mode() == VisibilityMode::VISIBLE)
        {
            for (auto const &item : group.items())
                paint_grid_item(painter, offset, d_pixmap_cache.get_pixmap(item.pixmap_code), item.scale, item.position, item.rotation);
        }
        else
        {
            if (!d_connection || !d_connection->is_server())
                continue;
            
            painter.setOpacity(0.5);
            for (auto const &item : group.items())
                paint_grid_item(painter, offset, d_pixmap_cache.get_pixmap(item.pixmap_code), item.scale, item.position, item.rotation);
            painter.setOpacity(1.0);
        }
    }

    painter.setPen(QPen{Qt::black});
    paint_grid(painter, size, offset);
}


void ApplicationControl::on_paint_player_layer(QPainter &painter, [[maybe_unused]] QSize size, QPoint offset, [[maybe_unused]] QPoint mouse)
{
    QMap<QString, Player> &players = d_player_control.players();

    for (auto &player : players)
    {
        QMap<QString, DrawLine> const &lines = player.lines();
        if (player.identifier() == d_player_control.own_identifier())
        {
            for (auto it = player.lines().begin(); it != player.lines().end(); ++it)
            {
                paint_line(painter,it.value().line, it.value().color, offset);
                if (auto it2 = d_line_selection.find(it.key()); it2 != d_line_selection.end())
                    paint_rect_around_line(painter, it.value().line, QColor{255, 0, 255}, offset);
            }
        }
        else
        {
            for (auto &line : lines)
                paint_line(painter, line.line, line.color, offset);
        }
    }
}


void ApplicationControl::on_paint_entity_layer(QPainter &painter, [[maybe_unused]] QSize size, QPoint offset, [[maybe_unused]] QPoint mouse)
{
    // paint all entities
    QMap<QString, Entity> entities = d_entity_manager.entities();
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        if (auto it2 = d_entity_selection.find(it.key()); it2 != d_entity_selection.end())
        {
            paint_player(painter, d_pixmap_cache.get_pixmap(it.value().avatar()), it.value().scale(), it.value().position(), offset, d_local_angle + it.value().rotation());
            paint_rect_around_pixmap(painter, it.value().position(), it.value().scale(), QColor{0, 255, 0}, offset);
        }
        else 
            paint_player(painter, d_pixmap_cache.get_pixmap(it.value().avatar()), it.value().scale(), it.value().position(), offset, it.value().rotation());
    }
    
    // paint all players
    QMap<QString, Player> &players = d_player_control.players();
    for (auto &player : players)
    {
        if (player.identifier() == "Dungeon Master")
            continue;
        paint_player(painter, d_pixmap_cache.get_pixmap(player.avatar_key()), player.size(), player.position(), offset);
    }
}


void ApplicationControl::on_paint_mouse_layer([[maybe_unused]] QPainter &painter, [[maybe_unused]] QSize size, [[maybe_unused]] QPoint offset, [[maybe_unused]] QPoint mouse)
{

}
