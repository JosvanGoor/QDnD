#include "chatwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

////////////////////
//  Constructors  //
////////////////////

ChatWidget::ChatWidget(QWidget *parent)
:   QWidget(parent)
{
    d_latest_message = 0;
    setLayout(new QVBoxLayout);

    layout()->addWidget(d_output = new QTextEdit);
    layout()->addWidget(d_input = new QLineEdit);
    layout()->addWidget(d_send = new QPushButton{"Send"});

    QFont font = d_output->font();
    font.setPointSize(12);
    d_output->setFont(font);

    d_output->setReadOnly(true);
    setMinimumWidth(300);

    QObject::connect(d_send, &QPushButton::pressed, this, &ChatWidget::on_send_pressed);
    QObject::connect(d_input, &QLineEdit::returnPressed, this, &ChatWidget::on_send_pressed);
}


ChatWidget::~ChatWidget()
{

}


////////////////////
//     Slots      //
////////////////////

QString ChatWidget::timestamp()
{
    QString stamp = "";
    size_t now = QDateTime::currentMSecsSinceEpoch() / 1000;
    if (d_latest_message != 0 && (now - d_latest_message) > 180) // 3 min
        stamp = "-----\n";
    d_latest_message = now;
    return (stamp + QDateTime::currentDateTime().toString("[hh:mm] "));
}


////////////////////
//     Slots      //
////////////////////

void ChatWidget::on_send_pressed()
{
    if (d_input->text().isEmpty())
        return;

    emit message_entered(d_input->text());
    d_input->setText("");
}


void ChatWidget::scroll_down()
{
    while (d_output->document()->blockCount() > 1000)
    {
        QTextCursor cursor{d_output->document()->firstBlock()};
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();
        cursor.deleteChar();
    }

    d_output->verticalScrollBar()->setValue(d_output->verticalScrollBar()->maximum());
}


void ChatWidget::on_info_message(QString const &message)
{
    QTextCursor cursor{d_output->document()};
    cursor.movePosition(QTextCursor::End);

    cursor.beginEditBlock();
    cursor.insertText(timestamp());
    cursor.insertText(message + "\n");
    cursor.endEditBlock();

    scroll_down();
}


void ChatWidget::on_user_message(QString const &name, QString const &message)
{
    QTextCursor cursor{d_output->document()};
    cursor.movePosition(QTextCursor::End);

    cursor.beginEditBlock();
    cursor.insertText(timestamp());
    cursor.insertText(name + ": ");
    cursor.insertText(message + "\n");
    cursor.endEditBlock();

    scroll_down();
}


void ChatWidget::on_rich_message(QString const &user, QString const &message)
{
    QTextCursor cursor{d_output->document()};
    cursor.movePosition(QTextCursor::End);

    cursor.beginEditBlock();
    cursor.insertText(timestamp());
    cursor.insertText(user + ": ");
    cursor.insertHtml(message);
    cursor.insertText("\n");
    cursor.endEditBlock();

    scroll_down();
}