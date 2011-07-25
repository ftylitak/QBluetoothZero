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

#ifndef QBTGLOBAL_H
#define QBTGLOBAL_H

#include <QtCore/qglobal.h>
#include <QtCore/QMetaType>

#ifdef BLUETOOTH_LIB
#define DLL_EXPORT Q_DECL_EXPORT
#else
#define DLL_EXPORT Q_DECL_IMPORT
#endif

#if QT_VERSION > 0x040603
#include <QtDeclarative/qdeclarative.h>
#endif

//#define ENABLE_QBLUETOOTH_NAMESPACE

#define QML_LIBRARY_NAME "QBluetooth"

#ifdef ENABLE_QBLUETOOTH_NAMESPACE
#define QBT_NAMESPACE_NAME QBluetooth
#define QBT_NAMESPACE_BEGIN	namespace QBT_NAMESPACE_NAME{
#define QBT_NAMESPACE_END	}
#else
#define QBT_NAMESPACE_NAME
#define QBT_NAMESPACE_BEGIN
#define QBT_NAMESPACE_END
#endif



#endif // QBTGLOBAL_H
