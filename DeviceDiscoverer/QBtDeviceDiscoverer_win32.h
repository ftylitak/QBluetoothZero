/*
 * QBtDeviceDiscoverer_stub.h
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTDEVICEDISCOVERER_STUB_H_
#define QBTDEVICEDISCOVERER_STUB_H_

#include <QBtTypes.h>
#include <QBtDeviceDiscoverer.h>

class QBtDeviceDiscovererPrivate
{
public:
    QBtDeviceDiscovererPrivate(QBtDeviceDiscoverer *publicClass = 0);
    ~QBtDeviceDiscovererPrivate();

public:
    void DiscoverDevices();
    void StopDiscovery();
    QBtDevice::List GetInquiredDevices();

protected:
    void Construct();

private:
    static void ReportInquiryResult(BTDEVHDL dev_hdl);
    static void InquiryCompleteResult(void);
    static void RegisterFoundDevice(BTDEVHDL dev_hdl);

private:
    static QBtDevice::List deviceList;
    // handle of the win event used to indicate that discovery finished
    static HANDLE browseDevEventHandler;
    static QBtDeviceDiscoverer* sp_ptr;
    static bool isSearching;

    QBtDeviceDiscoverer *p_ptr;  //Pointer to public interface
};

#endif /* QBTDEVICEDISCOVERER_STUB_H_ */
