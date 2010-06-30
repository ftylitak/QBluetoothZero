/*
 * QBtDeviceDiscoverer_stub.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtDeviceDiscoverer_stub.h"
#include "../QBtDeviceDiscoverer.h"

// ================= MEMBER FUNCTIONS =======================
//
// ---------------------------------------------------------
// QBtDeviceDiscovererPrivate::QBtDeviceDiscovererPrivate()
// Constructor
// ---------------------------------------------------------
//
QBtDeviceDiscovererPrivate::QBtDeviceDiscovererPrivate(QBtDeviceDiscoverer *wrapper) 
 : d_ptr(wrapper)
{
}


// ---------------------------------------------------------
// QBtDeviceDiscovererPrivate::~QBtDeviceDiscovererPrivate()
// Destructor
// ---------------------------------------------------------
//
QBtDeviceDiscovererPrivate::~QBtDeviceDiscovererPrivate()
{
}

// ---------------------------------------------------------
// QBtDeviceDiscovererPrivate::startSearch()
// Called to start searching for new devices
// ---------------------------------------------------------
//
void QBtDeviceDiscovererPrivate::DiscoverDevices()
{
    emit d_ptr->error(QBtDeviceDiscoverer::BluetoothNotSupported);
}

// ---------------------------------------------------------
// QBtDeviceDiscovererPrivate::startSearch()
// Called to stop searching
// ---------------------------------------------------------
//
void QBtDeviceDiscovererPrivate::StopDiscovery()
{
    emit d_ptr->error(QBtDeviceDiscoverer::BluetoothNotSupported);
}

QBtDevice::List QBtDeviceDiscovererPrivate::GetInquiredDevices()
{
	return QBtDevice::List();
}
