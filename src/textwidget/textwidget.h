#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class TextWidget : public QWidget
{
    Q_OBJECT

    QTextEdit *d_output;
    QLineEdit *d_input;
    QPushButton *d_send;

    public:
        explicit TextWidget(QWidget *parent = nullptr);
        ~TextWidget();
};

#endif