/*
 * QBtService.cpp
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtService.h"

QBtService::QBtService()
	: classUUID(QBtConstants::UndefinedClass),
	  name("Undefined"),
	  description("Undefined"),
	  handle(0),
	  port(0) 
{	
	protocolUUID.clear();
}

/*
QBtService::QBtService(const QBtService& service) :
	name(service.getName()), classUUID(service.getClass()), 
	port(service.getPort()), handle(service.getHandle()), 
	description(service.getDescription())
{
	protocolUUID = service.getProtocols();
}
*/

//////////////////////////////////////////////
//					Accessors				//
//////////////////////////////////////////////
QBtService::ProtocolList QBtService::getProtocols() const
{
	return protocolUUID;
}

QBtConstants::ServiceClass QBtService::getClass() const
{
	return classUUID;
}

QString QBtService::getName() const
{
	return name;
}

QString QBtService::getDescription() const
{
	return description;
}

unsigned int QBtService::getPort() const
{
	return port;
}

unsigned int QBtService::getHandle() const
{
	return handle;
}


//////////////////////////////////////////////
//				Mutators					//
//////////////////////////////////////////////

void QBtService::setClass(QBtConstants::ServiceClass newClass)
{
	classUUID = newClass;
}

void QBtService::setName(const QString& newName)
{
	name = newName;
}

void QBtService::setDescription(const QString& newDescription)
{
	description = newDescription;
}

void QBtService::setCommPort(unsigned int newPort)
{
	port = newPort;
}

void QBtService::setHandle(unsigned int newHandle)
{
	handle = newHandle;
}

void QBtService::setProtocols(QBtService::ProtocolList newUUIDs)
{
	protocolUUID = newUUIDs;
}

void QBtService::addProtocol(QBtConstants::ServiceProtocol uuid)
{
	if(protocolUUID.indexOf(uuid) == -1) // if not on list
		protocolUUID.append(uuid);
}

/**
 * Returns false if uuid not found in the protocol list
 */
bool QBtService::removeProtocol(QBtConstants::ServiceProtocol uuid)
{
	return protocolUUID.removeOne(uuid);
}

//////////////////////////////////////////
//				Operators				//	
//////////////////////////////////////////
/*
QBtService& QBtService::operator= (const QBtService& service)
{
	if ( this == &service )  
			return *this;
	
	name 			= service.getName();
	port 			= service.getPort();
	classUUID 		= service.getClass();
	protocolUUID 	= service.getProtocols();
	handle 			= service.getHandle();
	description 	= service.getDescription();
	
	
	return *this;
}
*/
