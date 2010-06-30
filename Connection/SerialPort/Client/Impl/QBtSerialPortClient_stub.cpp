/*
 * QBtSerialPortClient_stub.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtSerialPortClient_stub.h"

QBtSerialPortClientPrivate::QBtSerialPortClientPrivate(QBtSerialPortClient* publicClass) : 
	p_ptr(publicClass)
{
}

QBtSerialPortClientPrivate::~QBtSerialPortClientPrivate()
{
	
}

bool QBtSerialPortClientPrivate::IsConnected()
{
	return false;
}

void QBtSerialPortClientPrivate::Disconnect()
{
	
}

void QBtSerialPortClientPrivate::Connect(
		const QBtDevice& remoteDevice, 
		const QBtService& remoteService)
{
	
}

void QBtSerialPortClientPrivate::SendData(const QString& data)
{
	
}
