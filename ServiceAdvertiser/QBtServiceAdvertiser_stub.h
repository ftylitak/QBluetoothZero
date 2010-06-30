/*
 * QBtServiceAdvertiser_stub.h
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTSERVICEADVERTISER_STUB_H_
#define QBTSERVICEADVERTISER_STUB_H_

class QBtServiceAdvertiserPrivate
{
public:
	QBtServiceAdvertiserPrivate(QBtServiceAdvertiser* publicClass);
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
	QBtServiceAdvertiser* p_ptr;
};

#endif /* QBTSERVICEADVERTISER_STUB_H_ */
