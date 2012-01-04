#include "QBtAuxFunctions.h"

#ifdef Q_OS_WIN32
bool QBtAuxFunctions::InitBthSdk()
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

void QBtAuxFunctions::DeinitBthSdk()
{
    if(Btsdk_IsSDKInitialized() && sdkInitializationCounter > 0)
    {
        sdkInitializationCounter--;
        if(sdkInitializationCounter == 0)
            Btsdk_Done();
    }
}

BTDEVHDL QBtAuxFunctions::GetDeviceHandle(const QBtAddress& address)
{
    //get device handle
    BTDEVHDL devHandle = BTSDK_INVALID_HANDLE;
    BTUINT8 btAddr [6]= {0};
    QByteArray btAddrQt = address.toReversedByteArray();
    memcpy(btAddr, btAddrQt.constData(), btAddrQt.size());
    devHandle = Btsdk_GetRemoteDeviceHandle(btAddr);
    return devHandle;
}

#endif //WIN32
