/*
 * QBtSerialPortClient.cpp
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtSerialPortClient.h"
#include <QBtAuxFunctions.h>

#if defined(Q_OS_SYMBIAN)
#include "../QBtSerialPortClient_symbian.h"
#elif defined(Q_OS_WIN32)
#include "../QBtSerialPortClient_win32.h"
#elif !defined(Q_OS_WIN32) && !defined(Q_OS_SYMBIAN)
#include "../QBtSerialPortClient_stub.h"
#endif


//////////////////////////////////////////////////
// QBtSerialPortClient::QBtSerialPortClient()	//
// Defaul constructor							//
//////////////////////////////////////////////////
QBtSerialPortClient::QBtSerialPortClient(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_SYMBIAN
    QT_TRAP_THROWING(_implPtr = QBtSerialPortClientPrivate::NewL(this));
#else
    _implPtr = new QBtSerialPortClientPrivate(this);
#endif
}

QBtSerialPortClient::~QBtSerialPortClient()
{
    SafeDelete(_implPtr);
}

bool QBtSerialPortClient::isConnected()
{
    return _implPtr->IsConnected();
}

void QBtSerialPortClient::connect(const QBtDevice& remoteDevice, const QBtService& remoteService)
{
    _implPtr->Connect(remoteDevice, remoteService);
}

void QBtSerialPortClient::disconnect()
{
    _implPtr->Disconnect();
}
void QBtSerialPortClient::sendData(const QString& data)
{
    _implPtr->SendData(data);
}
