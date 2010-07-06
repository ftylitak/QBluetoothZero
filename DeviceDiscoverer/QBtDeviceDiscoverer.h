/*
 * QBtDeviceDiscoverer.h
 *
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTDEVICEDISCOVERER_H_
#define QBTDEVICEDISCOVERER_H_

#include <QBtGlobal.h>
#include <QObject>
#include <QBtTypes.h>

//Forward declaration
class QBtDeviceDiscovererPrivate;

/**
 * Class that contains the mechanism of the device discovery.
 * After instantiation, user can call startDiscovery() to begin the discovery.
 * If calling startDiscovery() is successfull then discoveryStarted() signal is emitted.
 * Any found device is reported through newDeviceFound(QBtDevice) signal or can be retrieved
 * calling GetInquiredDevices() which returns a list of all the found devices till now.
 * When discovery stops, discoveryStopped() signal is emitted.
 *
 * Incase of any errors, the are reported through
 * error(QBtDeviceDiscoverer::DeviceDiscoveryErrors) signal.
 */
class DLL_EXPORT QBtDeviceDiscoverer : public QObject
{
Q_OBJECT

public: //enums
    enum DeviceDiscoveryErrors
        { BluetoothNotSupported, BluetoothInUse, BluetoothAlreadyStopped, BluetoothNotReady,
        DiscoveryCancelled, UnknownError };

public:
    QBtDeviceDiscoverer(QObject* parent = 0);
    virtual ~QBtDeviceDiscoverer();

    /**
     * GetInquiredDevices()
     *
     * returns a reference to the list of devices found (if any)
     */
    const QBtDevice::List& getInquiredDevices() const;
    
    
    /**
     * Returns true if the class if performing a device discovery.
     */
    bool isBusy () const;

public slots:
    /**
     * startDiscovery()
     *
     * Start a device discovery.
     * The start and completion of device discovery are reported through
     * discoveryStarted() and discoveryStopped() signals respectively.
     */
    void startDiscovery();

    /**
     * stopDiscovery()
     *
     * Stops device discovery.
     * Signal discoveryStopped() is emitted.
     */
    void stopDiscovery();

signals:
    /**
     * Signaled for every device detected
     * @param remoteDevice The remote device
     */
    void newDeviceFound (const QBtDevice & remoteDevice);

    /**
     * Signal to report that discovery has stopped (either cancelled or no new devices to detect)
     */
    void discoveryStopped();

    /**
     * Signal to report that discovery has started. Alternative is error.
     */
    void discoveryStarted();

    /**
    * error
    * Signal to be emitted when error occurs.
    * @param error error code.
    */
    void error(QBtDeviceDiscoverer::DeviceDiscoveryErrors error);

private:        
    
    QBtDeviceDiscovererPrivate *_implPtr;    
    friend class QBtDeviceDiscovererPrivate;
    
};

#endif /* QBTDEVICEDISCOVERER_H_ */
