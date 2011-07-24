/*
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef QBTDEVICE_H
#define QBTDEVICE_H

#include <QtCore/QList>
#include <QtCore/QString>
#include <QBtGlobal.h>
#include <QBtService.h>
#include <QBtAddress.h>

//#include <QtDeclarative/QtDeclarative.h>

QBT_NAMESPACE_BEGIN

/**
 * The class that contains all the information needed about any bluetooth device.
 * Its main fields are 4.
 *
 * a) QBtAddress address: It is the device's bluetooth address.
 *                  Any communication between remote devices is made using this feild
 *                  so it is an essential information. No communication can be done
 *                  without this.
 *
 * b) QString name: The name of the device. By default this feild is equal to QBtAddress.toString().
 *                  The actual name is retrieved from the device discovery
 *                  and is set by the remote device as an identification string ID.
 *
 * c) DeviceMajor type: an enumeration field characterizing the device type.
 *
 * d) QBtService::List supportedServices: this field is updated after calling
 *                  QBtServiceDiscoverer::startDiscovery(QBtDevice*)
 *                  (if any services are found through SDP)
 */
class DLL_EXPORT QBtDevice : public QObject
{
	Q_OBJECT
	Q_ENUMS(DeviceMajor)
	Q_PROPERTY(QString name READ getName WRITE setName)
	Q_PROPERTY(QBtAddress address READ getAddress WRITE setAddress)
	Q_PROPERTY(DeviceMajor type READ getType WRITE setType)

public:
    typedef QList<QBtDevice> List;
    
    enum DeviceMajor
    {
        Uncategorized, 	//Uncategorized device
        Computer,		//Computer device
        Phone,			//Phone device
        LANAccess,		//Some form of a local area network router
        AudioVideo,		//Audio / Video device
        Peripheral,		//Mouse, Joystick, Keyboard
        Imaging,		//Camera or Scanner device
        Wearable,		//Wearable Device
        Toy,			//Toy device
        Miscellaneous	//Miscellaneous device
    };

public:
    QBtDevice(QObject* parent=0);

	/**
	 *  Copy constructor is needed by the QMetaType to register this custom class
	 */
    QBtDevice(const QBtDevice& dev, QObject* parent=0);
    QBtDevice (const QString & devName, const QBtAddress & devAddress, DeviceMajor devType, QObject* parent=0);
    ~QBtDevice();

    void addNewService (const QBtService& newService);
    //void setName (const QString & newName);
	void setName (const QString & newName);
    void setAddress (const QBtAddress& newAddress);
    void setType(DeviceMajor newType);
    void setSupportedServices (const QBtService::List& newSupportedServices);
    
    bool serviceListUpdated() const;

    QString getName() const;
    const QBtAddress& getAddress() const;
    DeviceMajor getType() const;
    QString getTypeAsString() const;
    const QBtService::List & getSupportedServices() const;
    
    // really needed? does not require special processing to copy the members
	//	->	It is required as it turns out when inheriting from QObject. If not implemented
	//		then i get linker error (at least when compiling for Windows)
    QBtDevice& operator= (const QBtDevice& dev);

private:
    QString _name;
    QBtAddress _address;
    DeviceMajor _type;
    QBtService::List _supportedServices;
    
    bool _serviceListUpdated;
};

QBT_NAMESPACE_END

Q_DECLARE_METATYPE(QBT_NAMESPACE_NAME::QBtDevice)
Q_DECLARE_METATYPE(QBT_NAMESPACE_NAME::QBtDevice::DeviceMajor)



#endif // QBTDEVICE_H


//QML_DECLARE_TYPE(type)