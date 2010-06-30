/*
 * QBtLocalDevice.cpp
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#include <QBtLocalDevice.h>
#include <QBtAuxFunctions.h>

#if defined(Q_OS_SYMBIAN)
#include "../QBtLocalDevice_symbian.h"
#elif defined(Q_OS_WIN32)
#include "../QBtLocalDevice_win32.h"
#elif !defined(Q_OS_WIN32) && !defined(Q_OS_SYMBIAN)
#include "../QBtLocalDevice_stub.h"
#endif

QBtAddress QBtLocalDevice::getLocalDeviceAddress()
{
    return QBtLocalDevicePrivate::GetLocalDeviceAddress();
}

bool QBtLocalDevice::getLimitedDiscoverableStatus()
{
    return QBtLocalDevicePrivate::GetLimitedDiscoverableStatus();
}

void QBtLocalDevice::setLimitedDiscoverableStatus(bool isDiscoverabilityLimited)
{
    QBtLocalDevicePrivate::SetLimitedDiscoverableStatus(isDiscoverabilityLimited);
}

QBtDevice::DeviceMajor QBtLocalDevice::getDeviceClass()
{
    return QBtLocalDevicePrivate::GetDeviceClass();
}

void QBtLocalDevice::setDeviceClass(QBtDevice::DeviceMajor classId)
{
    QBtLocalDevicePrivate::SetDeviceClass(classId);
}

void QBtLocalDevice::setLocalDeviceName(QString devName)
{
    QBtLocalDevicePrivate::SetLocalDeviceName(devName);
}

QString QBtLocalDevice::getLocalDeviceName()
{
    return QBtLocalDevicePrivate::GetLocalDeviceName();
}

////////////////////////////////

bool QBtLocalDevice::isBluetoothSupported()
{
    return QBtLocalDevicePrivate::IsBluetoothSupported();
}

void QBtLocalDevice::askUserTurnOnBtPower()
{
    QBtLocalDevicePrivate::AskUserTurnOnBtPower();
}

bool QBtLocalDevice::getBluetoothPowerState()
{
    return QBtLocalDevicePrivate::GetBluetoothPowerState();
}

bool QBtLocalDevice::setBluetoothPowerState (bool value)
{
	return QBtLocalDevicePrivate::SetBluetoothPowerState (value);
}

/////////////////////////////////

bool QBtLocalDevice::addNewDevice(const QBtDevice& device)
{
    return QBtLocalDevicePrivate::AddNewDevice(device);
}

bool QBtLocalDevice::deleteDevice(const QBtDevice& device)
{
    return QBtLocalDevice::deleteDevice(device.getAddress());
}

bool QBtLocalDevice::deleteDevice(const QBtAddress& address)
{
    return QBtLocalDevicePrivate::DeleteDevice(address);
}

bool QBtLocalDevice::unpairDevice(const QBtDevice& device)
{
    return QBtLocalDevice::unpairDevice(device.getAddress());
}

bool QBtLocalDevice::unpairDevice(const QBtAddress& address)
{
    return QBtLocalDevicePrivate::UnpairDevice(address);
}
