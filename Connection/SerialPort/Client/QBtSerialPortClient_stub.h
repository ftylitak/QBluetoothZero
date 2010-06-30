/*
 * QBtSerialPortClient_stub.h
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTSERIALPORTCLIENT_STUB_H_
#define QBTSERIALPORTCLIENT_STUB_H_

#include "./QBtSerialPortClient.h"

class QBtSerialPortClientPrivate
{
public:
	QBtSerialPortClientPrivate(QBtSerialPortClient* publicClass);
	~QBtSerialPortClientPrivate();
	
	bool IsConnected();
	void Disconnect();
	void Connect(const QBtDevice& remoteDevice, const QBtService& remoteService);
	void SendData(const QString& data);
	
private:
	QBtSerialPortClient* p_ptr;
};

#endif /* QBTSERIALPORTCLIENT_STUB_H_ */
