/*
 * QBtSerialPortServer.cpp
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtSerialPortServer.h"
#include <QBtAuxFunctions.h>

#if defined(Q_OS_SYMBIAN)
#include "../QBtSerialPortServer_symbian.h"
#elif defined(Q_OS_WIN32)
#include "../QBtSerialPortServer_win32.h"
#elif !defined(Q_OS_WIN32) && !defined(Q_OS_SYMBIAN)
#include "../QBtSerialPortServer_stub.h"
#endif


//////////////////////////////////////////////////
// QBtSerialPortServer::QBtSerialPortServer()	//
// Defaul constructor							//
//////////////////////////////////////////////////
QBtSerialPortServer::QBtSerialPortServer(QObject *parent) :
    QObject(parent), _advertiser(NULL), _service(NULL), _isConnected(false) 
{
#ifdef Q_OS_SYMBIAN
    QT_TRAP_THROWING(_implPtr = QBtSerialPortServerPrivate::NewL(this));
#else
    _implPtr = new QBtSerialPortServerPrivate(this);
#endif
}

QBtSerialPortServer::~QBtSerialPortServer()
{
    SafeDelete(_implPtr);
    SafeDelete(_service);
}

void QBtSerialPortServer::startServer(const QString& serviceName)
{
    QBtService tmpService;
    tmpService.setName(serviceName);
    setTransmittingService(tmpService);

    _implPtr->StartListener();
}

void QBtSerialPortServer::stopServer()
{
    _implPtr->StopListener();
}

void QBtSerialPortServer::sendData(const QString data)
{
    _implPtr->SendData(data);
}

bool QBtSerialPortServer::isConnected()
{
    return _isConnected;
}

QBtService QBtSerialPortServer::getTransmittingServiceInfo()
{
    if(_service)
        return *_service;
    else
        return QBtService();
}

void QBtSerialPortServer::setTransmittingService(const QBtService& service)
{
    SafeDelete(_service);
    _service = new QBtService(service);
}

void QBtSerialPortServer::setConnectionStatus(bool connected)
{
    _isConnected = connected;
}

void QBtSerialPortServer::startAdvertisingService(const QBtService& service)
{
    setTransmittingService(service);
    _advertiser = new QBtServiceAdvertiser(this);
    _advertiser->startAdvertising(service);
}

void QBtSerialPortServer::stopAdvertisingService()
{
    if(_advertiser)
    {
        _advertiser->stopAdvertising();
        delete _advertiser;
        _advertiser = NULL;
    }
}
