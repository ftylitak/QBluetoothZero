#ifndef QCHATWIDGET_H
#define QCHATWIDGET_H

#include <QString>
#include <QAction>

#include "ui_chatWidget.h"

class QChatWidget : public QWidget
{
public:
	QChatWidget(QWidget* parent = NULL);
	virtual ~QChatWidget();
	
	void SetName(QString newName);
	QString GetName();
	
protected:
	void SetupUI();
	
protected:
	QString name;
	QWidget* spaceWidget;
	
	QAction* optionAction;
	QAction* closeAction;
	
	 Ui::chatWidget ui;
};

#endif //QCHATWIDGET_H
