/*
 * QBtObjectExchangeServer_stub.h
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTOBJECTEXCHANGESERVER_STUB_H_
#define QBTOBJECTEXCHANGESERVER_STUB_H_

#include "QBtObjectExchangeServer.h"

class QBtObjectExchangeServerPrivate
{
public:
	QBtObjectExchangeServerPrivate(QBtObjectExchangeServer publicClass);
	~QBtObjectExchangeServerPrivate();
	
	bool StartServer();
	void Disconnect();
	bool IsConnected();
	
private:
	QBtObjectExchangeServer p_ptr;
};


#endif /* QBTOBJECTEXCHANGESERVER_STUB_H_ */
