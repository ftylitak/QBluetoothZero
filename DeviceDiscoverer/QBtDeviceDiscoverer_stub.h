/*
 * QBtDeviceDiscoverer_stub.h
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTDEVICEDISCOVERER_STUB_H_
#define QBTDEVICEDISCOVERER_STUB_H_

#include <QBtDevice.h>
#include <QBtDeviceDiscoverer.h>

class QBtDeviceDiscovererPrivate
{
public:
    QBtDeviceDiscovererPrivate(QBtDeviceDiscoverer *wrapper = 0);
    ~QBtDeviceDiscovererPrivate();

public:
    void DiscoverDevices();
    void StopDiscovery();
    const QBtDevice::List& GetInquiredDevices() const;

private: // Daa
    QBtDeviceDiscoverer *d_ptr;  //Pointer to public interface
};

#endif /* QBTDEVICEDISCOVERER_STUB_H_ */
