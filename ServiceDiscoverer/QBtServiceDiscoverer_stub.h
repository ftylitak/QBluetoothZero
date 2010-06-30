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
    void DiscoverSpecificProtocol(QBtDevice* targetDevice, QBtConstants::ServiceClass uuid);
    void StopDiscovery();
    QBtService::List GetSupportedServices();
    
    

private:
    QBtServiceDiscoverer* p_ptr;  //Pointer to public interface
};

#endif /* QBTSERVICEDISCOVERER_STUB_H_ */
