#ifndef QCHATWIDGETSERVER_H
#define QCHATWIDGETSERVER_H

#include "QChatWidget.h"
#include <QBluetoothZero.h>
#include <QMenu>

class QChatWidgetServer : public QChatWidget
{
    Q_OBJECT
public:
    QChatWidgetServer(QWidget*parent);
    ~QChatWidgetServer();

    void SetServer(QBtSerialPortServer* btServer);
    void SetDiscoverer(QBtDeviceDiscoverer* discoverer);

private:
    void Setup();

private slots:
    void clientDisconnectedReport();
    void dataReceivedReport(QString data);
    void errorReport(QBtSerialPortServer::ErrorCode code);
    void newDeviceFoundReport(QBtDevice foundDevice);
    void discoveryStoppedReport();
    void sendLineEditData();
    void sendMessageRequest();

signals:
    void tabNameChanged(QString newName, QChatWidget* tab);

private:
    QBtSerialPortServer* server;
    QBtAddress clientAddress;
    QBtDeviceDiscoverer* devDisc;
    QMenu* menu;
};

#endif //QCHATWIDGETSERVER_H
