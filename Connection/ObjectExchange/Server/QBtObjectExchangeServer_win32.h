/*
 * QBtObjectExchangeServer_win32.h
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTOBJECTEXCHANGESERVER_WIN32_H_
#define QBTOBJECTEXCHANGESERVER_WIN32_H_

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

#endif /* QBTOBJECTEXCHANGESERVER_WIN32_H_ */
