/*
 * QBtServiceAdvertiser_symbian.h
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTSERVICEADVERTISER_SYMBIAN_H_
#define QBTSERVICEADVERTISER_SYMBIAN_H_

// INCLUDES
#include <e32base.h>

#include <coecntrl.h>
#include <es_sock.h>
#include <btdevice.h>
#include <bt_sock.h>
#include <btsdp.h>
#include <btmanclient.h>

#include <QBtTypes.h>
#include <QBtServiceAdvertiser.h>

class QBtServiceAdvertiserPrivate  : public CBase
{
public:
    /*!
     * NewL(QBtServiceAdvertiser* publicClass)
     *
     * Create new QBtServiceAdvertiserPrivate object
     * return a pointer to the created instance of QBtServiceAdvertiserPrivate
     */
    static QBtServiceAdvertiserPrivate* NewL(QBtServiceAdvertiser* publicClass);

    /*!
     * NewLC(QBtServiceAdvertiser* publicClass)
     *
     */
    static QBtServiceAdvertiserPrivate* NewLC(QBtServiceAdvertiser* publicClass);

    /*!
     * ~CDeviceDiscoverer()
     *
     * Destroy the object and release all memory objects
     */
    ~QBtServiceAdvertiserPrivate();

    /*!
     * StartAdvertiser(const QBtService& service)
     *
     * Starts the service advertiser.
     *
     * param service the service class that contains all the necessery
     * information for transmitting the service
     */
    void StartAdvertiser(const QBtService& service);

    /*!
     * StopAdvertiser()
     *
     * Stops the service advertiser.  our entry from service
     * discovery database will be removed.
     */
    void StopAdvertiser();

    /*!
     * UpdateAvailability()
     *
     * Updates the availability of advertised service.  the service
     * record in service discovery database will be updated accordingly.
     *
     * param aAvailable true if the service should be set as available,
     * false if unavailable.
     */
    void UpdateAvailability(TBool aAvailable);

private:

    /*!
     * QBtServiceAdvertiserPrivate(QBtServiceAdvertiser* publicClass)
     *
     * Perform the first phase of two phase construction
     */
    QBtServiceAdvertiserPrivate(QBtServiceAdvertiser* publicClass);

    /*!
     * ConstructL()
     *
     */
    void ConstructL();

private:

    // service discovery protocol session
    RSdp iSdp;
    // service discovery database (sdp)
    RSdpDatabase iSdpDB;
    // service record
    TSdpServRecordHandle iRecord;
    // service record state
    TInt iRecordState;

    // local service to advertise
    QBtService* localService;

    //pointer to parent object (from constructor). Not owned by this class
    QBtServiceAdvertiser *p_ptr;
};

#endif /* QBTSERVICEADVERTISER_SYMBIAN_H_ */
