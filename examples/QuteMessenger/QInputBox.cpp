#include <QInputBox.h>

QInputBox::QInputBox(QWidget* parent) : QTextEdit(parent)
{
}

void QInputBox::keyReleaseEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Enter)
    {
        emit enterPressed();
    }
}
