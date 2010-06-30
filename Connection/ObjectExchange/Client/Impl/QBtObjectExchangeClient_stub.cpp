/*
 * QBtObjectExchangeClient_stub.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtObjectExchangeClient_stub.h"

QBtObjectExchangeClientPrivate::QBtObjectExchangeClientPrivate(
		QBtObjectExchangeClient* publicClass) : p_ptr(publicClass)
{
}

QBtObjectExchangeClientPrivate::~QBtObjectExchangeClientPrivate()
{
	
}

void QBtObjectExchangeClientPrivate::ConnectToServer(const QBtDevice& remoteDevice, const QBtService& remoteService)
{
	
}

void QBtObjectExchangeClientPrivate::Disconnect()
{
	
}

void QBtObjectExchangeClientPrivate::SendFile(const QString& fileName)
{
	
}

void QBtObjectExchangeClientPrivate::SendData(
		const QByteArray& data, const QString& bufferName)
{
	
}

void QBtObjectExchangeClientPrivate::Abort()
{
	
}

bool QBtObjectExchangeClientPrivate::IsConnected()
{
	return false;
}

bool QBtObjectExchangeClientPrivate::IsBusy()
{
	return false;
}

bool QBtObjectExchangeClientPrivate::SetPath(const QString path)
{
	return false;
}

void QBtObjectExchangeClientPrivate::GetFile(
		const QString& localPath, const QString& remoteFileNameFull)
{
	
}

void QBtObjectExchangeClientPrivate::GetByteBuffer(const QString& dataName)
{
	
}
