/*
 * QBtServiceDiscoverer_stub.h
 *
 *
 *      Author: Ftylitakis Nikolaos
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

#ifndef QBTSERVICEDISCOVERER_STUB_H_
#define QBTSERVICEDISCOVERER_STUB_H_

#include <QBtUuid.h>
#include <QBtDevice.h>
#include <QBtServiceDiscoverer.h>
#include <QBtAuxFunctions.h>
#include <QObject>

class QBtServiceDiscovererPrivate : public QObject
{
Q_OBJECT

public:
    QBtServiceDiscovererPrivate(QBtServiceDiscoverer* publicClass);
    ~QBtServiceDiscovererPrivate();

    void DiscoverServices(QBtDevice* targetDevice);
    void DiscoverSpecificClass(QBtDevice* targetDevice, QBtConstants::ServiceClass uuid);
    void DiscoverSpecificProtocol(QBtDevice* targetDevice, QBtConstants::ServiceProtocol uuid);
    void StopDiscovery();
	void DiscoverSpecificClasses(QBtDevice* targetDevice, const QList<QBtUuid> &uuids);    
	void DiscoverRfcommServices(QBtDevice* targetDevice);
	void DiscoverObexServices(QBtDevice* targetDevice);
    bool IsBusy() const;

protected:
    void Construct();

private:
    void ProcessFoundServices(BTSVCHDL* foundServices, int numOfServices, QBtConstants::ServiceClass wantedClass);
    void RetrieveSPPAttributes(QBtService* currService, BTSVCHDL servHandle);
	void DiscoverServiceHandles(QBtDevice* targetDevice, BTSVCHDL** servicesFound, BTUINT32* numOfServicesFound, QBtConstants::ServiceClass uuid);

private slots:
	void SetBusy();
	void SetNotBusy();

private:
    QBtServiceDiscoverer *p_ptr;  //Pointer to public interface
	bool isBusy;
};

#endif /* QBTSERVICEDISCOVERER_STUB_H_ */
