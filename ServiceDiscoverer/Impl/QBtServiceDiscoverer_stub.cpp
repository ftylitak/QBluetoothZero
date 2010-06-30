/*
 * QBtServiceDiscoverer_stub.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtServiceDiscoverer_stub.h"

QBtServiceDiscovererPrivate::QBtServiceDiscovererPrivate(QBtServiceDiscoverer* publicClass):
	p_ptr(publicClass)
{
}

QBtServiceDiscovererPrivate::~QBtServiceDiscovererPrivate()
{	
}

void QBtServiceDiscovererPrivate::DiscoverServicesOnDevice(QBtDevice* targetDevice)
{
	return;
}

void QBtServiceDiscovererPrivate::DiscoverSpecificProtocol(
			QBtDevice* targetDevice, QBtConstants::ServiceClass uuid)
{
	return;
}

void QBtServiceDiscovererPrivate::StopDiscovery()
{
	return;
}

QBtService::List QBtServiceDiscovererPrivate::GetSupportedServices()
{
	return QBtService::List();
}
