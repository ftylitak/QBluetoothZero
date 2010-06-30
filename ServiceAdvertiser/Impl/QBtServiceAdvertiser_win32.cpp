/*
 * QBtServiceAdvertiser_stub.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtServiceAdvertiser_win32.h"

QBtServiceAdvertiserPrivate::QBtServiceAdvertiserPrivate(QBtServiceAdvertiser* publicClass) 
	: p_ptr(publicClass)
{
}

QBtServiceAdvertiserPrivate::~QBtServiceAdvertiserPrivate()
{	
}

void QBtServiceAdvertiserPrivate::StartAdvertiser(const QBtService& /*service*/)
{
	emit p_ptr->error(QBtServiceAdvertiser::FeatureNotSupported);
	return;
}

void QBtServiceAdvertiserPrivate::StopAdvertiser()
{
    emit p_ptr->error(QBtServiceAdvertiser::FeatureNotSupported);
	return;
}

void QBtServiceAdvertiserPrivate::UpdateAvailability(bool /*aAvailable*/)
{
	emit p_ptr->error(QBtServiceAdvertiser::FeatureNotSupported);
	return;
}
