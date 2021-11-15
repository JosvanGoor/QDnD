#include "textwidget.h"

void TextWidget::add_text(QString const &str)
{
    QTextCursor cursor{d_output->document()};
    cursor.movePosition(QTextCursor::End);
    
    cursor.beginEditBlock();
    cursor.insertText(str);
    cursor.insertText("\n");
    cursor.endEditBlock();

    while (d_output->document()->blockCount() > 2500)
    {
        QTextCursor cursor{d_output->document()->firstBlock()};
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();
        cursor.deleteChar();
    }
}