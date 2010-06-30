/*
 * QBtLocalDevice_symbian.h
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTLOCALDEVICE_SYMBIAN_H_
#define QBTLOCALDEVICE_SYMBIAN_H_

#include <e32base.h>
#include <e32std.h>
#include <featureinfo.h>
#include <featdiscovery.h>
#include <btnotifierapi.h>
#include <centralrepository.h>
#include <BTServerSDKCRKeys.h>
#include <btdevice.h>
#include <btmanclient.h>
#include <e32property.h>
#include <bt_subscribe.h>

#include <QBtLocalDevice.h>

class QBtLocalDevicePrivate
{
public:

    ///////////////////////////////////////
    ///	 Bluetooth local properties		///
    ///////////////////////////////////////
    static QBtAddress GetLocalDeviceAddress();
    static TBool GetLimitedDiscoverableStatus();
    static void SetLimitedDiscoverableStatus(TBool limited);
    static QBtDevice::DeviceMajor GetDeviceClass();
    static void SetDeviceClass(QBtDevice::DeviceMajor classId);
    static void SetLocalDeviceName(QString devName);
    static QString GetLocalDeviceName();


    ///////////////////////////////
    ///	 Bluetooth Hardware		///
    ///////////////////////////////
    static TBool IsBluetoothSupported();
    static void AskUserTurnOnBtPower();
    static TBool GetBluetoothPowerState();
    static TBool SetBluetoothPowerState (TBool value); 


    ///////////////////////////////
    ///	 Bluetooth Registry		///
    ///////////////////////////////
    static TBool AddNewDevice(const QBtDevice& device);
    static TBool DeleteDevice(const QBtAddress& address);
    static TBool UnpairDevice(const QBtAddress& address);

private:
    static TBool DefineProperty(TUint propertyId, RProperty::TType typeEnum);
    static TBool DeleteOrUnpairDevice(const QBtAddress& address, TBool unpair);

private:
    QBtLocalDevice* p_ptr;
};

#endif /* QBTLOCALDEVICE_SYMBIAN_H_ */
