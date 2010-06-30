/*
 * QBtSerialPortClient_win32.h
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTSERIALPORTCLIENT_WIN32_H_
#define QBTSERIALPORTCLIENT_WIN32_H_

#include "./QBtSerialPortClient.h"
#include "../../WinSerialPort/Tserial_event.h"

class QBtSerialPortClientPrivate
{
public:
	QBtSerialPortClientPrivate(QBtSerialPortClient* publicClass);
	~QBtSerialPortClientPrivate();
	
	bool IsConnected();
	void Disconnect();
	/**
	* Connect()
	* Connect to the server
	* INFO: if remoteService has no handle information then the classId
	* field is used to connect. (Tested class id working QBtConstants::SerialPort)
	*
	* @param remoteDevice the remote server to connect to
	* @param remoteServive the remote service of the server
	*/
	void Connect(const QBtDevice& remoteDevice, const QBtService& remoteService);
	void SendData(const QString& data);
	
private:
	/**
	 * PLugInCommPort()
	 * Plug in a virtual comm port given by the OS.
	 * This comm port will be used later on to communicate.
	 */
	bool PLugInCommPort();
	void DeinitializeCommPort();
	
	/*
	 * ConnectBtSerialPortProfile_Handle()
	 * This function is called when remoteService has a valid handle.
	 * and the connecting port.
	 */
	bool ConnectBtSerialPortProfile_Handle();
	
	/*
	 * ConnectBtSerialPortProfile_ServClass()
	 * Used when the only info provided about the service is its class
	 * and the connecting port.
	 */
	bool ConnectBtSerialPortProfile_ServClass();
	
	bool InitializeSerialPortHandle();
	void CloseSerialPortHandle();
	
	static void SerialEventManager(uint32 object, uint32 event);
	void SerialCallback(Tserial_event *com_source, uint32 event);
	
private:
	// the server device info
	QString incomingDataBuffer;
	BTUINT32 OSComPort;
	HANDLE serialHandle;
	
	QBtDevice* server;
	QBtService* connectingService;
	BTCONNHDL connectionHandle;
	Tserial_event *com;
	
	// Qt parent public class
	QBtSerialPortClient* p_ptr;
};

#endif /* QBTSERIALPORTCLIENT_WIN32_H_ */
