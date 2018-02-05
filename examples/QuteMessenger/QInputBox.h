#include <QTextEdit>
#include <QKeyEvent>

class QInputBox : public QTextEdit
{
Q_OBJECT

public:
    QInputBox(QWidget* parent);
    void keyReleaseEvent(QKeyEvent* e);

signals:
    void enterPressed();
};
