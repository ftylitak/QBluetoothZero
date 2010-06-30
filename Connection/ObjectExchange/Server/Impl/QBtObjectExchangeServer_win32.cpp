/*
 * QBtObjectExchangeServer_win32.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtObjectExchangeServer_win32.h"

QBtObjectExchangeServerPrivate::QBtObjectExchangeServerPrivate(
		QBtObjectExchangeServer publicClass) : p_ptr(publicClass)
{
}

QBtObjectExchangeServerPrivate::~QBtObjectExchangeServerPrivate()
{	
}

bool QBtObjectExchangeServerPrivate::StartServer()
{
	return false;
}

void QBtObjectExchangeServerPrivate::Disconnect()
{	
}

bool QBtObjectExchangeServerPrivate::IsConnected()
{
	return false;
}
