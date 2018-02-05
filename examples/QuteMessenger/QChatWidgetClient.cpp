/*
 * QChatWidgetClient.cpp
 *
 *      Author: Ftylitakis Nikolaos
 */

#include "QChatWidgetClient.h"
#include <QAction>
#include <QBtAuxFunctions.h>

QChatWidgetClient::QChatWidgetClient(QWidget* parent)
    : QChatWidget(parent), device(NULL), service(NULL), client(NULL)
{
    optionAction = NULL;
    Setup();

    connect(ui.lineEdit, SIGNAL(enterPressed()), this, SLOT(sendMessageRequest()));
}

QChatWidgetClient::~QChatWidgetClient()
{
    if(client)
    {
        disconnect(client, SIGNAL(connectedToServer()));
        disconnect(client, SIGNAL(disconnectedFromServer()));
        disconnect(client, SIGNAL(dataReceived(const QString)));
        disconnect(client, SIGNAL(error(QBtSerialPortClient::ErrorCode)));
    }

    SafeDelete(client);
    SafeDelete(device);
    SafeDelete(service);

    if(optionAction)
        removeAction(optionAction);

    SafeDelete(optionAction);
}

void QChatWidgetClient::Setup()
{
    //connect(lineEdit,SIGNAL(returnPressed()),
        //	this, SLOT(sendMessageRequest()));
//	menu = new QMenu(this);

    optionAction = new QAction(tr("Send"), this);
    optionAction->setSoftKeyRole(QAction::PositiveSoftKey);
    connect(optionAction, SIGNAL(triggered()), this, SLOT(sendMessageRequest()));
    addAction(optionAction);

    ui.textEdit->append("---Connected---");
    //menu->addAction(optionAction);
}

void QChatWidgetClient::StartSerialPortClient()
{
    SafeDelete(client);
    client = new QBtSerialPortClient(this);

    connect(client, SIGNAL(connectedToServer()),
            this, SLOT(connectedToServerReport()));

    connect(client, SIGNAL(disconnectedFromServer()),
            this, SLOT(disconnectedFromServerReport()));

    connect(client, SIGNAL(dataReceived(const QString)),
            this, SLOT(dataReceivedReport(const QString)));

    connect(client, SIGNAL(error(QBtSerialPortClient::ErrorCode)),
            this, SLOT(errorReport(QBtSerialPortClient::ErrorCode)));

    client->connect(*device, *service);
}

void QChatWidgetClient::setParameters(QBtDevice dev, QBtService serv)
{
    device = new QBtDevice(dev);
    service = new QBtService(serv);

    StartSerialPortClient();
}

void QChatWidgetClient::connectedToServerReport()
{
    ui.textEdit->append("---Connected---");
}

void QChatWidgetClient::disconnectedFromServerReport()
{
    ui.textEdit->append("---Disconnected---");
//	lineEdit->setEditFocus(false);
}

void QChatWidgetClient::dataReceivedReport(const QString data)
{
    QString str("-> ");
    str += data;

    ui.textEdit->append(str);
}

void QChatWidgetClient::errorReport(QBtSerialPortClient::ErrorCode code)
{
    QString str("--Error occurred: ");
        str += code;

    ui.textEdit->append(str);
}

//Called to send data typed in QLineEdit
void QChatWidgetClient::sendMessageRequest()
{
    const QString data = QString::fromUtf16(ui.lineEdit->toPlainText().utf16());
    if(client)
    {
        client->sendData(data);
        QString sendingString("<- ");
        sendingString += data;
        ui.textEdit->append(sendingString);
        ui.lineEdit->setText("");
    }
}
