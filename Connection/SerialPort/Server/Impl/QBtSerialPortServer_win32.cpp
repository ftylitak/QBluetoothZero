/*
 * QBtSerialPortServer_stub.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtSerialPortServer_win32.h"

QBtSerialPortServerPrivate::QBtSerialPortServerPrivate(QBtSerialPortServer* publicClass) : 
		p_ptr(publicClass)
{	
}

QBtSerialPortServerPrivate::~QBtSerialPortServerPrivate()
{
	emit p_ptr->error(QBtSerialPortServer::BluetoothSPSNotSupported);
}

void QBtSerialPortServerPrivate::StartListener()
{
	emit p_ptr->error(QBtSerialPortServer::BluetoothSPSNotSupported);
}

void QBtSerialPortServerPrivate::StopListener()
{
	emit p_ptr->error(QBtSerialPortServer::BluetoothSPSNotSupported);
}

void QBtSerialPortServerPrivate::SendData(const QString /*data*/)
{
	emit p_ptr->error(QBtSerialPortServer::BluetoothSPSNotSupported);
}
