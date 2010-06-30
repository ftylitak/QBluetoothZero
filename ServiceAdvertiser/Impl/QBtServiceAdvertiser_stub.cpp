/*
 * QBtServiceAdvertiser_stub.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtServiceAdcertiser_stub.h"

QBtServiceAdvertiserPrivate::QBtServiceAdvertiserPrivate(QBtServiceAdvertiser* publicClass) 
	: p_ptr(publicClass)
{
}

QBtServiceAdvertiserPrivate::~QBtServiceAdvertiserPrivate()
{	
}

void QBtServiceAdvertiserPrivate::StartAdvertiser(const QBtService& service)
{
	return;	
}

void QBtServiceAdvertiserPrivate::StopAdvertiser()
{
	return;
}

void QBtServiceAdvertiserPrivate::UpdateAvailability(TBool aAvailable)
{
	return;
}
