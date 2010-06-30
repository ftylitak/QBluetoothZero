/*
 * QBtDeviceDiscoverer_symbian.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */
#include "../QBtDeviceDiscoverer_symbian.h"
#include "../QBtDeviceDiscoverer.h"
#include <bt_sock.h> 
#include <bttypes.h>

_LIT(KBTLinkManagerTxt,"BTLinkManager");

QBtDeviceDiscovererPrivate* QBtDeviceDiscovererPrivate::NewL(QBtDeviceDiscoverer *publicClass)
{
	QBtDeviceDiscovererPrivate* self = QBtDeviceDiscovererPrivate::NewLC(publicClass);
	CleanupStack::Pop(self);
	return self;
}


QBtDeviceDiscovererPrivate* QBtDeviceDiscovererPrivate::NewLC(QBtDeviceDiscoverer *publicClass)
{
	QBtDeviceDiscovererPrivate* self = new (ELeave) QBtDeviceDiscovererPrivate(publicClass);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}


void QBtDeviceDiscovererPrivate::ConstructL()
{
	User::LeaveIfError(iSocketServ.Connect());
	TProtocolName protocolName(KBTLinkManagerTxt);
	User::LeaveIfError(iSocketServ.FindProtocol(protocolName,iProtocolInfo)); 
}


// ----------------------------------------------------------------------------
// CDeviceDiscoverer::CDeviceDiscoverer(RSocketServ *aSocketServ,
//                                      MDeviceDiscoObserver *aObserver)
//
// constructor
// ----------------------------------------------------------------------------
QBtDeviceDiscovererPrivate::QBtDeviceDiscovererPrivate(QBtDeviceDiscoverer *publicClass):
	CActive(CActive::EPriorityStandard), iLIAC(false), sizeOfListeningQueue(4), p_ptr(publicClass) 
{
	CActiveScheduler::Add(this);
	iDevList = new QBtDevice::List();
}


// ----------------------------------------------------------------------------
// CDeviceDiscoverer::~CDeviceDiscoverer()
//
// destructor
// ----------------------------------------------------------------------------
QBtDeviceDiscovererPrivate::~QBtDeviceDiscovererPrivate()
{ 
	// cancel active object
	if(IsActive())
		Cancel();
	
	//iResolver.Close();
	delete iDevList;
}


// ----------------------------------------------------------------------------
// CDeviceDiscoverer::DiscoverDevicesL(TDeviceDataList *aDevDataList)
//
// discover remote devices.  RHostResolver will be used to do the discovery.
// any found devices will be placed in aDevDataList.
// ----------------------------------------------------------------------------
void QBtDeviceDiscovererPrivate::DiscoverDevices()
{
	if (!IsActive())
	{
		// initialize host resolver
		// load protocol for discovery
		iResolver.Close();
		TInt err = iResolver.Open(iSocketServ, iProtocolInfo.iAddrFamily, iProtocolInfo.iProtocol);
		if (err) 
		{
			emit p_ptr->error(QBtDeviceDiscoverer::UnknownError);
			return;
		}

		// wipe existing device data list, start fresh
		iDevList->clear();

		// start device discovery by invoking remote address lookup
		TUint myIAC(iLIAC ? KLIAC : KGIAC);
		iAddr.SetIAC(myIAC);

		iAddr.SetAction(KHostResInquiry|KHostResName|KHostResIgnoreCache);
		iResolver.GetByAddress(iAddr, iEntry, iStatus);
		emit p_ptr->discoveryStarted();
		SetActive();
	}
	else
	{
		emit p_ptr->error(QBtDeviceDiscoverer::BluetoothInUse);
		return;
	}
}


void QBtDeviceDiscovererPrivate::RunL()
{
	// RHostResolver.GetByAddress(..) has completed, process results
	if ( iStatus == KErrNone )
	{
		TBTSockAddr address = iEntry().iAddr;
		TBTDevAddr btAddress = address.BTAddr();
		
		//QByteArray btAddressArray((const char*)btAddress.Des().Ptr(), 6); 
		QBtAddress qtBtDeviceAddress(btAddress);
		
		THostName nameDevice = iEntry().iName;
		QString qtNameDevice = QString::fromUtf16(nameDevice.Ptr(),nameDevice.Length());        

		TInquirySockAddr& sa = TInquirySockAddr::Cast( iEntry().iAddr );
		//TUint8 minorClass = sa.MinorClassOfDevice();
		//quint8 qMinorClass = quint8(minorClass);  
		
		//Set major device class
		TUint16 majorClass = sa.MajorClassOfDevice();
		QBtDevice::DeviceMajor qtDeviceMajorClass;
		switch (majorClass) {
		case 0x00: //computer
			qtDeviceMajorClass = QBtDevice::Miscellaneous;
			break;	     
		case 0x01:
			qtDeviceMajorClass = QBtDevice::Computer;
			break;	
		case 0x02:
			qtDeviceMajorClass = QBtDevice::Phone;
			break;
		case 0x03:
			qtDeviceMajorClass = QBtDevice::LANAccess;
			break;   	
		case 0x04:
			qtDeviceMajorClass = QBtDevice::AudioVideo;
			break;         	
		case 0x05:
			qtDeviceMajorClass = QBtDevice::Peripheral;
			break;     
		case 0x06:
			qtDeviceMajorClass = QBtDevice::Imaging;
			break;   
		default:
			qtDeviceMajorClass = QBtDevice::Uncategorized;
			break;
		}
		
		//QBtDevice* remoteDevice = new QBtDevice(qtNameDevice, qtBtDeviceAddress, qtDeviceMajorClass);
		QBtDevice remoteDevice (qtNameDevice, qtBtDeviceAddress, qtDeviceMajorClass);		
		
		QT_TRYCATCH_LEAVING (emit p_ptr->newDeviceFound(remoteDevice) );
		
		
		// store on list
		iDevList->append (remoteDevice);

		
		// next
		iResolver.Next(iEntry,iStatus);
		SetActive();
	}
	else if (iStatus == KErrHostResNoMoreResults) {
        //Note emit may throw. We translate to Leave here.
        QT_TRYCATCH_LEAVING (emit p_ptr->discoveryStopped() );
	}
    else {
        QT_TRYCATCH_LEAVING (emit p_ptr->discoveryStopped());
		//ErrorConvertToLocalL(iStatus.Int());
    }
}

void QBtDeviceDiscovererPrivate::DoCancel()
{
	//Note that must trap any errors here - Cancel is called in destructor and destructor must not throw.
	QT_TRY
	{
		emit p_ptr->discoveryStopped();
	}
	QT_CATCH (std::exception&) {}
	
	iResolver.Cancel();
}

// ----------------------------------------------------------------------------
// CDeviceDiscoverer::HasDevices()
//
// returns true if any devices were discovered
// ----------------------------------------------------------------------------
TBool QBtDeviceDiscovererPrivate::HasDevices()
{
	//TBool exists = EFalse;
	return iDevList->size() > 0;
}

// ----------------------------------------------------------------------------
// CBluetoothPMPExampleEngine::SetLIAC
// ----------------------------------------------------------------------------
void QBtDeviceDiscovererPrivate::SetLIAC( TBool aState )
{
	iLIAC = aState;
}

// ----------------------------------------------------------------------------
// CBluetoothPMPExampleEngine::StopDiscovery
// ----------------------------------------------------------------------------
void QBtDeviceDiscovererPrivate::StopDiscovery()
{
	if (IsActive()) 
		Cancel();
	else
	{
		//Note, may throw. That is OK, stopSearch() is called from Qt code only.
		emit p_ptr->error(QBtDeviceDiscoverer::BluetoothAlreadyStopped);
	}
}

// ----------------------------------------------------------------------------
// QBtDeviceDiscovererPrivate::GetInquiredDevices
// Gets the list of devices that where found during the last search
// ----------------------------------------------------------------------------
const QBtDevice::List& QBtDeviceDiscovererPrivate::GetInquiredDevices() const
{
	return *iDevList;	
}
