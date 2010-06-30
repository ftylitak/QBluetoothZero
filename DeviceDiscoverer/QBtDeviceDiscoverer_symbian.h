/*
 * QBtDeviceDiscoverer_symbian.h
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTDEVICEDISCOVERER_SYMBIAN_H_
#define QBTDEVICEDISCOVERER_SYMBIAN_H_

#include <e32base.h>
#include <ES_SOCK.H>
#include <bt_sock.h>

#include <QBtDevice.h>
#include <QBtDeviceDiscoverer.h>

class QBtDeviceDiscovererPrivate : public CActive
{
public:

/*!
 * NewL()
 * Create new CDeviceDiscoverer object
 * return a pointer to the created instance of CDeviceDiscoverer
 */
    static QBtDeviceDiscovererPrivate* NewL(QBtDeviceDiscoverer *publicClass);

/*!
 * NewLC()
 */
    static QBtDeviceDiscovererPrivate* NewLC(QBtDeviceDiscoverer *publicClass);

/*!
 * ~CDeviceDiscoverer()
 *	the object and release all memory objects
 */
    ~QBtDeviceDiscovererPrivate();

/*!
 * DiscoverDevicesL()
 * Discovers remote bluetooth devices within range.
 * param aDevDataList device data list where the found devices will be placed.
 */
    void DiscoverDevices();

/*!
 * StopDiscovery()
 * Stops ongoing device discovery
 *
 */
    void StopDiscovery();

/*!
 * HasDevices()
 * any devices discovered?
 * return true if any devices were discovered.
 */
    TBool HasDevices();

/*!
 * SetLIAC()
 * Set LimitedDiscoverableStatus status
 *
 */
    void SetLIAC( TBool aState );

    /*
     * Gets the list of devices that where found during the last search
     */
    const QBtDevice::List& GetInquiredDevices() const;

protected:

/*!
 * RunL()
 * Handle the active objects request completion.
 */
    void RunL();

/*!
 * DoCancel()
 * Cancels the outstanding request on active object.
 */
    void DoCancel();


private:

/*!
 * CDeviceDiscoverer()
 * Perform the first phase of two phase construction
 * param aSocketServ reference to socket server
 */
    QBtDeviceDiscovererPrivate(QBtDeviceDiscoverer *publicClass);

/*!
 * ConstructL()
 */
    void ConstructL();

private: //data

    // socket server handle
    RSocketServ iSocketServ;
    // device data list, to be filled by resolver results
    QBtDevice::List *iDevList;
    // host resolver
    RHostResolver iResolver;
    TInquirySockAddr iAddr;
    TProtocolDesc iProtocolInfo;
    TNameEntry iEntry;
    TBool iLIAC;

    TInt sizeOfListeningQueue;

    //pointer to parent object (from constructor). Not owned by this class
    QBtDeviceDiscoverer *p_ptr;
};

#endif /* QBTDEVICEDISCOVERER_SYMBIAN_H_ */
