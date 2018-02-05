/*
 * QChatWidgetClient.h
 *
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QCHATWIDGETCLIENT_H_
#define QCHATWIDGETCLIENT_H_

#include "QChatWidget.h"
#include <QBluetoothZero.h>
#include <QMenu>

class QChatWidgetClient : public QChatWidget
{
    Q_OBJECT

public:
    QChatWidgetClient(QWidget* parent);
    ~QChatWidgetClient();

private:
    void Setup();
    void StartSerialPortClient();

public slots:
    void setParameters(QBtDevice dev, QBtService serv);

private slots:
    void sendMessageRequest();

    void connectedToServerReport();
    void disconnectedFromServerReport();
    void dataReceivedReport(const QString data);
    void errorReport(QBtSerialPortClient::ErrorCode code);

private:
    QBtSerialPortClient* client;
    QBtDevice* device;
    QBtService* service;
    QMenu* menu;
};

#endif /* QCHATWIDGETCLIENT_H_ */
