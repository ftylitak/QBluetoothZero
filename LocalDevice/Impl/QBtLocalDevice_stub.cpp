/*
 * QBtLocalDevice_stub.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtLocalDevice_stub.h"

TBool QBtLocalDevicePrivate::isBluetoothSupported()
{
	return false;
}

void QBtLocalDevicePrivate::AskUserTurnOnBtPower()
{
	return;
}

bool QBtLocalDevicePrivate::GetBluetoothPowerState()
{
	return false;
}

bool QBtLocalDevicePrivate::SetBluetoothPowerState (bool value)
{
	return false;
}



QBtAddress QBtLocalDevicePrivate::GetLocalDeviceAddress()
{
	return QBtAddress();
}

bool QBtLocalDevicePrivate::GetLimitedDiscoverableStatus()
{
	return false;
}

void QBtLocalDevicePrivate::SetLimitedDiscoverableStatus(bool isDiscoverabilityLimited)
{
	
}

QBtDevice::DeviceMajor QBtLocalDevicePrivate::GetDeviceClass()
{
	return QBtDevice::Uncategorized;
}

void QBtLocalDevicePrivate::SetDeviceClass(QBtDevice::DeviceMajor classId)
{
	
}

void QBtLocalDevicePrivate::SetLocalDeviceName(QString devName)
{
	
}

QString QBtLocalDevicePrivate::GetLocalDeviceName()
{
	return "";
}

bool QBtLocalDevicePrivate::AddNewDevice(const QBtDevice& device)
{
	return false;
}

bool QBtLocalDevicePrivate::DeleteDevice(const QBtDevice& device)
{
	return false;
}

bool QBtLocalDevicePrivate::DeleteDevice(const QBtAddress& address)
{
	return false;
}

bool QBtLocalDevicePrivate::UnpairDevice(const QBtDevice& device)
{
	return false;
}
