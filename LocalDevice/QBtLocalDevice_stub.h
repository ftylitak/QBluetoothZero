/*
 * QBtLocalDevice_stub.h
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTLOCALDEVICE_STUB_H_
#define QBTLOCALDEVICE_STUB_H_

class QBtLocalDevicePrivate
{
public:
	
	///////////////////////////////////////
	///	 Bluetooth local properties		///
	///////////////////////////////////////
	static QBtAddress GetLocalDeviceAddress();
	static bool GetLimitedDiscoverableStatus();
	static void SetLimitedDiscoverableStatus(bool isDiscoverabilityLimited);
	static QBtDevice::DeviceMajor GetDeviceClass();
	static void SetDeviceClass(QBtDevice::DeviceMajor classId);
	static void SetLocalDeviceName(QString devName);
	static QString GetLocalDeviceName();

	
	///////////////////////////////
	///	 Bluetooth Hardware		///
	///////////////////////////////
	static bool IsBluetoothSupported();
	static void AskUserTurnOnBtPower();
	static bool GetBluetoothPowerState();
	static bool SetBluetoothPowerState (bool value); 
	

	///////////////////////////////
	///	 Bluetooth Registry		///
	///////////////////////////////
	static bool AddNewDevice(const QBtDevice& device);
	static bool DeleteDevice(const QBtDevice& device);
	static bool DeleteDevice(const QBtAddress& address);
	static bool UnpairDevice(const QBtDevice& device);
	static bool UnpairDevice(const QBtAddress& address);

};

#endif /* QBTLOCALDEVICE_STUB_H_ */
