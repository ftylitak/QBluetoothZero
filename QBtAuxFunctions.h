/*
 * auxFunctions_symbian.h
 *
 *      Author: Ftylitakis Nikolaos
 */

#ifndef AUXFUNCTIONS_SYMBIAN_H_
#define AUXFUNCTIONS_SYMBIAN_H_

template<class T> inline void SafeDelete(T* &ptr)
{
	if(ptr)
	{
		delete ptr;
		ptr = NULL; 
	}
}


#ifdef Q_OS_WIN32

#include <windows.h>
#include <conio.h>

extern "C"{
#include "./BlueSoleil_SDK_2.0.5/include/Btsdk_ui.h"
}

using namespace std;


// used to have the number of the classes that use the Bluesoleil SDK.
// if the number reaches zero the sdk is deinitialized.
static size_t sdkInitializationCounter = 0;

static bool InitBthSdk()
{
	if ( sdkInitializationCounter == 0) /* not connected with BlueSoleil */
	{
		if (Btsdk_Init() != BTSDK_OK)
			return false;

		if (Btsdk_IsBluetoothReady() == BTSDK_FALSE)
			Btsdk_StartBluetooth();
			
		BTUINT16 discoveryFlags = BTSDK_CONNECTABLE | BTSDK_PAIRABLE | BTSDK_GENERAL_DISCOVERABLE;
		Btsdk_SetDiscoveryMode(discoveryFlags);
		Btsdk_SetLocalDeviceClass(BTSDK_COMPCLS_DESKTOP);
	}
	sdkInitializationCounter++;
	
	return true;
}

static void DeinitBthSdk()
{
	if(Btsdk_IsSDKInitialized() && sdkInitializationCounter > 0)
	{
		sdkInitializationCounter--;
		if(sdkInitializationCounter == 0)
			Btsdk_Done();
	}
}

static BTDEVHDL GetDeviceHandle(QBtAddress& address)
{
	//get device handle
	BTDEVHDL devHandle = BTSDK_INVALID_HANDLE;
	BTUINT8 btAddr [6]= {0};
	QByteArray btAddrQt = address.toReversedByteArray();
	memcpy(btAddr, btAddrQt.constData(), btAddrQt.size());
	devHandle = Btsdk_GetRemoteDeviceHandle(btAddr);
	return devHandle;
}
#endif // Q_OS_WIN32

#endif /* AUXFUNCTIONS_SYMBIAN_H_ */
