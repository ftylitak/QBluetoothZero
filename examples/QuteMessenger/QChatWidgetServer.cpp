/*
 * QChatWidgetServer.cpp
 *
 *      Author: Ftylitakis Nikolaos
 */

#include "QChatWidgetServer.h"
#include <QBtAuxFunctions.h>

QChatWidgetServer::QChatWidgetServer(QWidget*parent) : QChatWidget(parent), server(NULL)
{
    optionAction = NULL;
    Setup();
    connect(ui.lineEdit, SIGNAL(enterPressed()), this, SLOT(sendMessageRequest()));
}

QChatWidgetServer::~QChatWidgetServer()
{
    if(devDisc)
        devDisc->stopDiscovery();

    if(optionAction)
        removeAction(optionAction);

    if(server)
        server->stopServer();

    SafeDelete(optionAction);

    if(devDisc)
    {
        disconnect(devDisc, SIGNAL(newDeviceFound(QBtDevice)),
            this, SLOT(newDeviceFoundReport(QBtDevice)));

        disconnect(devDisc, SIGNAL(discoveryStopped()),
            this, SLOT(discoveryStoppedReport()));
    }
}

void QChatWidgetServer::Setup()
{
    //connect(lineEdit,SIGNAL(returnPressed()),
        //	this, SLOT(sendLineEditData()));
    //menu = new QMenu(this);

    optionAction = new QAction(tr("Send"), this);
    optionAction->setSoftKeyRole(QAction::PositiveSoftKey);
    connect(optionAction, SIGNAL(triggered()), this, SLOT(sendMessageRequest()));
    addAction(optionAction);
    //menu->addAction(optionAction);

    ui.textEdit->append("---Connected---");
}

void QChatWidgetServer::SetDiscoverer(QBtDeviceDiscoverer* discoverer)
{
    devDisc = discoverer;
}

void QChatWidgetServer::SetServer(QBtSerialPortServer* btServer)
{
    server = btServer;

    connect(server, SIGNAL(clientDisconnected()),
            this, SLOT(clientDisconnectedReport()));

    connect(server, SIGNAL(dataReceived(QString)),
            this, SLOT(dataReceivedReport(QString)));

    connect(server, SIGNAL(error(QBtSerialPortServer::ErrorCode)),
            this, SLOT(errorReport(QBtSerialPortServer::ErrorCode)));

    //start device discovery to get the name of the client device

    if(devDisc)
    {
        connect(devDisc, SIGNAL(newDeviceFound(QBtDevice)),
                this, SLOT(newDeviceFoundReport(QBtDevice)));

        connect(devDisc, SIGNAL(discoveryStopped()),
                this, SLOT(discoveryStoppedReport()));

        devDisc->startDiscovery();
    }
}

void QChatWidgetServer::clientDisconnectedReport()
{
    ui.textEdit->append("---Disconnected---");
    //lineEdit->setEditFocus(false);
}

void QChatWidgetServer::dataReceivedReport(QString data)
{
    QString strToWrite("-> ");
    strToWrite += data;
    //textEdit->insertHtml( strToWrite);
    ui.textEdit->append(strToWrite);
}

void QChatWidgetServer::errorReport(QBtSerialPortServer::ErrorCode code)
{
    ui.textEdit->append("--Error occurred: " + code);
}

void QChatWidgetServer::newDeviceFoundReport(QBtDevice foundDevice)
{
    if(foundDevice.getAddress().toString() == name)
    {
        devDisc->stopDiscovery();

        name = foundDevice.getName();
        ui.messageLogBox->setTitle(name);

        emit tabNameChanged(name, this);
    }
}

void QChatWidgetServer::discoveryStoppedReport()
{
    disconnect(devDisc, SIGNAL(newDeviceFound(QBtDevice)),
                this, SLOT(newDeviceFoundReport(QBtDevice)));

    disconnect(devDisc, SIGNAL(discoveryStopped()),
            this, SIGNAL(discoveryStoppedReport()));
}

void QChatWidgetServer::sendLineEditData()
{
    const QString data = QString::fromUtf8(ui.lineEdit->toPlainText().toUtf8());
    if(server)
    {
        server->sendData(data);
        QString sendingString("<- ");
        sendingString += data;
        //textEdit->insertHtml(sendingString);
        ui.textEdit->append(sendingString);
        ui.lineEdit->setText("");
    }

}

void QChatWidgetServer::sendMessageRequest()
{
    sendLineEditData();
}
