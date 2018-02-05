/*
 * ChatWidget.cpp
 *
 *      Author: Ftylitakis Nikolaos
 */

#include "QChatWidget.h"
#include <QFont>

QChatWidget::QChatWidget(QWidget* parent) : QWidget(parent), name("Chat")
{
	SetupUI();
}

QChatWidget::~QChatWidget()
{	
	if(closeAction)
		delete closeAction;
}

void QChatWidget::SetupUI()
{
    setObjectName(QString::fromUtf8("this"));
    setContextMenuPolicy(Qt::NoContextMenu);
	
	ui.setupUi(this);

	closeAction = new QAction(tr("Close"), this);
	closeAction->setSoftKeyRole(QAction::NegativeSoftKey);
	connect(closeAction, SIGNAL(triggered()), parent(), SLOT(closeCurrentTab()));
	addAction(closeAction);
}

void QChatWidget::SetName(QString newName)
{
	name = newName;
	if(ui.messageLogBox)
		ui.messageLogBox->setTitle(newName);
}

QString QChatWidget::GetName()
{
	return name;
}
