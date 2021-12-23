#include "mainwindow.h"

////////////////////
//  Constructors  //
////////////////////

MainWindow::MainWindow(QWidget *parent)
:   QMainWindow(parent)
{
    d_entity_tab = nullptr;
    setCentralWidget(d_central_widget = new QSplitter);

    d_central_widget->addWidget(d_middle_widget = new QSplitter);
    
    d_middle_widget->addWidget(d_middle_tabs = new QTabWidget);
    d_middle_widget->addWidget(d_debug_output = new QTextEdit);

    d_middle_tabs->addTab(d_display_tab = new DisplayWidget, "Display");
    d_middle_tabs->addTab(d_spells_tab = new SpellsWidget, "Spells");
    d_middle_tabs->addTab(d_grid_tab = new GridWidget, "Grid");
    d_middle_tabs->setCurrentIndex(2); // TODO: remove
    
    d_central_widget->addWidget(d_right_tabs = new QTabWidget);
    d_right_tabs->addTab(d_chat_tab = new ChatWidget, "Chat");
    d_right_tabs->addTab(d_players_tab = new PlayersWidget, "Players");
    d_right_tabs->addTab(d_grid_control_tab = new GridControlWidget{d_grid_tab}, "Grid Control");

    d_middle_widget->setOrientation(Qt::Vertical);
    d_middle_widget->setSizes({600, 100});
    d_debug_output->setReadOnly(true);
    d_central_widget->setSizes({1200, 400});

    setMenuBar(d_menu_bar = new MenuBar);
    setStatusBar(d_status_bar = new StatusBar);

    load_entity_widget();

    resize(1600, 900);
}


MainWindow::~MainWindow()
{
    
}


////////////////////
//     Slots      //
////////////////////

ChatWidget *MainWindow::chat_widget() noexcept
{
    return d_chat_tab;
}


DisplayWidget *MainWindow::display_widget() noexcept
{
    return d_display_tab;
}


EntityWidget *MainWindow::entity_widget() noexcept
{
    return d_entity_tab;
}


GridControlWidget *MainWindow::grid_control_widget() noexcept
{
    return d_grid_control_tab;
}


GridWidget *MainWindow::grid_widget() noexcept
{
    return d_grid_tab;
}


MenuBar *MainWindow::menu_bar() noexcept
{
    return d_menu_bar;
}

PlayersWidget *MainWindow::players_widget() noexcept
{
    return d_players_tab;
}


SpellsWidget *MainWindow::spells_widget() noexcept
{
    return d_spells_tab;
}

StatusBar *MainWindow::status_bar() noexcept
{
    return d_status_bar;
}


////////////////////
//    Utility     //
////////////////////

void MainWindow::load_entity_widget()
{
    d_right_tabs->addTab(d_entity_tab = new EntityWidget, "Entity Control");
}


void MainWindow::unload_entity_widget()
{
    delete d_entity_tab;
    d_entity_tab = nullptr;
}


////////////////////
//     Slots      //
////////////////////

void MainWindow::debug_message(QString const &message)
{
    QTextCursor cursor{d_debug_output->document()};
    cursor.movePosition(QTextCursor::End);

    cursor.beginEditBlock();
    cursor.insertText(message + "\n");
    cursor.endEditBlock();

    while (d_debug_output->document()->blockCount() > 1000)
    {
        QTextCursor cursor{d_debug_output->document()->firstBlock()};
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();
        cursor.deleteChar();
    }

    d_debug_output->verticalScrollBar()->setValue(d_debug_output->verticalScrollBar()->maximum());
}