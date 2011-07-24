/*
 * QBtService.cpp
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

#include "../QBtService.h"

QBT_NAMESPACE_BEGIN

//____________________________________________________________________________

QBtService::QBtService(QObject* parent) 
   : QObject(parent),
	 _name ("Undefined"),
     _description ("Undefined"),
     _handle(0),
     _port(0)
{	
    _protocolList.clear();
}

QBtService::QBtService(const QBtService& service, QObject* parent) : QObject(parent)
{
	_serviceUuid = service.getClass();
	_protocolList = service.getProtocols();
	_name = service.getName();
	_description = service.getDescription();
	_handle = service.getHandle();
	_port = service.getHandle();
}


//____________________________________________________________________________

QBtService::ProtocolList QBtService::getProtocols() const
{
    return _protocolList;
}

//____________________________________________________________________________

QBtUuid QBtService::getClass() const
{
    return _serviceUuid;
}

//____________________________________________________________________________

QString QBtService::getName() const
{
    return _name;
}


//____________________________________________________________________________

QString QBtService::getDescription() const
{
    return _description;
}


//____________________________________________________________________________

uint QBtService::getPort() const
{
    return _port;
}


//____________________________________________________________________________

uint QBtService::getHandle() const
{
    return _handle;
}


//____________________________________________________________________________

void QBtService::setClass (const QBtUuid & newClass)
{
    _serviceUuid = newClass;
}


//____________________________________________________________________________

void QBtService::setName(const QString& newName)
{
    _name = newName;
}


//____________________________________________________________________________

void QBtService::setDescription(const QString& newDescription)
{
    _description = newDescription;
}


//____________________________________________________________________________

void QBtService::setPort (uint newPort)
{
    _port = newPort;
}


//____________________________________________________________________________

void QBtService::setHandle(uint newHandle)
{
    _handle = newHandle;
}

//____________________________________________________________________________

void QBtService::setProtocols(const QBtService::ProtocolList & newUuids)
{
    _protocolList = newUuids;
}


//____________________________________________________________________________

void QBtService::addProtocol(const QBtUuid & uuid)
{
    if (_protocolList.indexOf (uuid) == -1) // if not on list
        _protocolList.append (uuid);
}


//____________________________________________________________________________
//
// Returns false if uuid not found in the protocol list

bool QBtService::removeProtocol (const QBtUuid & uuid)
{
    return _protocolList.removeOne(uuid);
}

QBtService& QBtService::operator=(const QBtService& service)
{
	if(this != &service)
	{
		_serviceUuid = service.getClass();
		_protocolList = service.getProtocols();
		_name = service.getName();
		_description = service.getDescription();
		_handle = service.getHandle();
		_port = service.getHandle();
	}
	return *this;
}

QBT_NAMESPACE_END
