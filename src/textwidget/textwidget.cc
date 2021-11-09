#include "textwidget.h"

TextWidget::TextWidget(QWidget *parent)
:   QWidget(parent)
{
    setLayout(new QVBoxLayout);

    d_output = new QTextEdit;
    d_output->setReadOnly(true);
    layout()->addWidget(d_output);

    QWidget *input_widget = new QWidget;
    input_widget->setLayout(new QHBoxLayout);
    d_input = new QLineEdit;
    d_send = new QPushButton("Send");
    input_widget->layout()->addWidget(d_input);
    input_widget->layout()->addWidget(d_send);
    layout()->addWidget(input_widget);

    setMinimumWidth(300);
}


TextWidget::~TextWidget()
{

}