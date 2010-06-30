/*
 * QBtDeviceDiscoverer.cpp
 *
 *
 *      Author: Ftylitakis Nikolaos
 */
#include "../QBtDeviceDiscoverer.h"
#include <QBtAuxFunctions.h>

#if defined(Q_OS_SYMBIAN)
#include "../QBtDeviceDiscoverer_symbian.h"
#elif defined(Q_OS_WIN32)
#include "../QBtDeviceDiscoverer_win32.h"
#elif !defined(Q_OS_WIN32) && !defined(Q_OS_SYMBIAN)
#include "../QBtDeviceDiscoverer_stub.h"
#endif


//////////////////////////////////////////////////
// QBtDeviceDiscoverer::QBtDeviceDiscoverer()	//
// Defaul constructor							//
//////////////////////////////////////////////////
QBtDeviceDiscoverer::QBtDeviceDiscoverer(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_SYMBIAN
    QT_TRAP_THROWING(_implPtr = QBtDeviceDiscovererPrivate::NewL(this));
#else
    _implPtr = new QBtDeviceDiscovererPrivate(this);
#endif
}

//////////////////////////////////////////////////
// QBtDeviceDiscoverer::~QBtDeviceDiscoverer()	//
// Destructor									//
//////////////////////////////////////////////////
QBtDeviceDiscoverer::~QBtDeviceDiscoverer()
{
    SafeDelete(_implPtr);
}

//////////////////////////////////////////////////
// BluetoothDiscovery::startSearch()			//
// Called to start searching for new devices	//
//////////////////////////////////////////////////
void QBtDeviceDiscoverer::startDiscovery()
{
    _implPtr->DiscoverDevices();
}

//////////////////////////////////////////////////
// BluetoothDiscovery::stopSearch()				//
// Called to stop searching for new devices		//
//////////////////////////////////////////////////
void QBtDeviceDiscoverer::stopDiscovery()
{
    _implPtr->StopDiscovery();
}

//////////////////////////////////////////////////
// BluetoothDiscovery::stopSearch()				//
// Called to stop searching for new devices		//
//////////////////////////////////////////////////
const QBtDevice::List& QBtDeviceDiscoverer::getInquiredDevices() const
{
    return _implPtr->GetInquiredDevices();
}

