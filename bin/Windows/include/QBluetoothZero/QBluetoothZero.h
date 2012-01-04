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

#ifndef QBLUETOOTH_H
#define QBLUETOOTH_H

#include <QBtAuxFunctions.h>
#include <QBtGlobal.h>

#include <QBtTypes.h>
#include <QBtDeviceDiscoverer.h>
#include <QBtSingleDeviceSelectorUI.h>
#include <QBtServiceDiscoverer.h>
#include <QBtServiceDiscovererForAll.h>
#include <QBtServiceAdvertiser.h>
#include <QBtSerialPortServer.h>
#include <QBtSerialPortClient.h>
#include <QBtObjectExchangeClient.h>
#include <QBtObjectExchangeServer.h>
#include <QBtLocalDevice.h>

//using namespace QBluetooth;

namespace QBluetooth
{
    static void registerTypes()
    {
        qRegisterMetaType<QBT_PREPEND_NAMESPACE(QBtDevice)>("QBtDevice");
        qRegisterMetaType<QBT_PREPEND_NAMESPACE(QBtService)>("QBtService");
        qRegisterMetaType<QBT_PREPEND_NAMESPACE(QBtAddress)>("QBtAddress");
        qRegisterMetaType<QBT_PREPEND_NAMESPACE(QBtUuid)>("QBtUuid");
        qRegisterMetaType<QBT_PREPEND_NAMESPACE(QBtRemoteFileInfo)>("QBtRemoteFileInfo");
    }

    static void registerQMLTypes()
    {
       /* #if QT_VERSION > 0x040700
        qmlRegisterType<QBT_PREPEND_NAMESPACE(QBtConstants)>(QML_LIBRARY_NAME, 1, 0, "QBtConstants");
        qmlRegisterType<QBT_PREPEND_NAMESPACE(QBtUuid)>(QML_LIBRARY_NAME, 1, 0, "QBtUuid");
        qmlRegisterType<QBT_PREPEND_NAMESPACE(QBtAddress)>(QML_LIBRARY_NAME, 1, 0, "QBtAddress");
        qmlRegisterType<QBT_PREPEND_NAMESPACE(QBtDevice)>(QML_LIBRARY_NAME, 1, 0, "QBtDevice");
        qmlRegisterType<QBT_PREPEND_NAMESPACE(QBtService)>(QML_LIBRARY_NAME, 1, 0, "QBtService");
        qmlRegisterType<QBT_PREPEND_NAMESPACE(QBtDeviceDiscoverer)>(QML_LIBRARY_NAME, 1, 0, "QBtDeviceDiscoverer");
        qmlRegisterType<QBT_PREPEND_NAMESPACE(QBtRemoteFileInfo)>(QML_LIBRARY_NAME, 1, 0, "QBtRemoteFileInfo");
        //qmlRegisterType<QBtServiceDiscoverer>("QBtServiceDiscoverer", 1, 0, "QBtServiceDiscoverer");
        //qmlRegisterType<QBtServiceAdvertiser>("QBtServiceAdvertiser", 1, 0, "QBtServiceAdvertiser");
        //qmlRegisterType<QBtLocalDevice>("QBtLocalDevice", 1, 0, "QBtLocalDevice");
        //qmlRegisterType<QBtSingleDeviceSelectorUI>("QBtSingleDeviceSelectorUI", 1, 0, "QBtSingleDeviceSelectorUI");
        //qmlRegisterType<QBtSerialPortServer>("QBtSerialPortServer", 1, 0, "QBtSerialPortServer");
        //qmlRegisterType<QBtSerialPortClient>("QBtSerialPortClient", 1, 0, "QBtSerialPortClient");
        //qmlRegisterType<QBtObjectExchangeServer>("QBtObjectExchangeServer", 1, 0, "QBtObjectExchangeServer");
        //qmlRegisterType<QBtObjectExchangeClient>("QBtObjectExchangeClient", 1, 0, "QBtObjectExchangeClient");
        #endif*/
    }

}

#endif // QBLUETOOTH_H
