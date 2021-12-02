#ifndef VIEW_CHATWIDGET_H
#define VIEW_CHATWIDGET_H

#include <QLineEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextEdit>
#include <QWidget>

class ChatWidget : public QWidget
{
    Q_OBJECT

    QTextEdit *d_output;
    QLineEdit *d_input;
    QPushButton *d_send;

    public:
        explicit ChatWidget(QWidget *parent = nullptr);
        ~ChatWidget();

    public slots:
        void on_send_pressed();
        void scroll_down();

        void on_info_message(QString const &message);
        void on_user_message(QString const &user, QString const &message);
        void on_rich_message(QString const &user, QString const &expression);

    signals:
        void message_entered(QString const &str);


};

#endif