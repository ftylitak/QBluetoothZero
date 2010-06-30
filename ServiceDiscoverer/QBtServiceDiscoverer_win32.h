/*
 * QBtServiceDiscoverer_stub.h
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTSERVICEDISCOVERER_STUB_H_
#define QBTSERVICEDISCOVERER_STUB_H_

#include <QBtDevice.h>
#include <QBtServiceDiscoverer.h>

class QBtServiceDiscovererPrivate
{
public:
    QBtServiceDiscovererPrivate(QBtServiceDiscoverer* publicClass);
    ~QBtServiceDiscovererPrivate();

    void DiscoverServicesOnDevice(QBtDevice* targetDevice);
    void DiscoverSpecificClass(QBtDevice* targetDevice, QBtConstants::ServiceClass uuid);
    void DiscoverSpecificProtocol(QBtDevice* targetDevice, QBtConstants::ServiceProtocol uuid);
    void StopDiscovery();

protected:
    void Construct();

private:
    void ProcessFoundServices(BTSVCHDL* foundServices, int numOfServices);
    void RetrieveSPPAttributes(QBtService* currService, BTSVCHDL servHandle);

private:
    QBtServiceDiscoverer *p_ptr;  //Pointer to public interface
};

#endif /* QBTSERVICEDISCOVERER_STUB_H_ */
