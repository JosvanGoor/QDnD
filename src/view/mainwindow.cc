#include "mainwindow.h"

////////////////////
//  Constructors  //
////////////////////

MainWindow::MainWindow(QWidget *parent)
:   QMainWindow(parent)
{
    setCentralWidget(d_central_widget = new QSplitter);

    d_central_widget->addWidget(d_middle_widget = new QSplitter);
    
    d_middle_widget->addWidget(d_middle_tabs = new QTabWidget);
    d_middle_widget->addWidget(d_debug_output = new QTextEdit);
    
    d_middle_tabs->addTab(d_spells_tab = new SpellsWidget, "Spells");
    
    d_central_widget->addWidget(d_left_tabs = new QTabWidget);

    d_middle_widget->setOrientation(Qt::Vertical);
    d_middle_widget->setSizes({600, 100});
    d_debug_output->setReadOnly(true);
}


MainWindow::~MainWindow()
{
    
}


////////////////////
//     Slots      //
////////////////////

SpellsWidget *MainWindow::spells_widget() noexcept
{
    return d_spells_tab;
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