/*
 * QBtObjectExchangeClient_stub.h
 *
 *  
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTOBJECTEXCHANGECLIENT_STUB_H_
#define QBTOBJECTEXCHANGECLIENT_STUB_H_

class QBtObjectExchangeClientPrivate
{
public:

	QBtObjectExchangeClientPrivate(QBtObjectExchangeClient* publicClass);
	~QBtObjectExchangeClientPrivate();

	/**
	* ConnectToServer
	* Connect to the server
	* INFO: if remoteService has no handle information then the classId
	* field is used to connect. (Tested class id working QBtConstants::OBEXFileTransfer)
	*
	* @param remoteDevice the remote server to connect to
	* @param remoteServive the remote service of the server
	*/
	void ConnectToServer(const QBtDevice& remoteDevice, const QBtService& remoteService);

	/**
	* Disconnect
	* Disconnect from the remote machine, by sending an
	* OBEX disconnect, and closing the transport on (and
	* regardless of) response from the server.
	*/
	void Disconnect();

	/**
	* SendFile
	* Send a file to a service on a remote machine
	*/
	void SendFile(const QString& fileName);

	/**
	* SendData
	* Send a byte array to a service on a remote machine
	*/
	void SendData(const QByteArray& data, const QString& bufferName);


	/**
	* Abort
	* Send the OBEX aborts command to the remote machine
	*/
	void Abort();

	/**
	* IsConnected
	* @return true if the client is connected
	*/
	bool IsConnected();

	/**
	* IsBusy
	* @return true if the client is performing some operation.
	*/
	bool IsBusy();

	/**
	* SetPath()
	* Set the current path of the remote device OBEX session.
	*/
	bool SetPath(const QString & path);

	/**
	* GetFile
	* 
	* Request from the server to GET the file defined in the argument
	*/
	void GetFile(const QString& localPath, const QString& remoteFileNameFull);

	/**
	* GetByteBuffer()
	* 
	* Request from the server to GET the data buffer defined in the argument
	*/
	void GetByteBuffer(const QString& dataName);
	
private:
	QBtObjectExchangeClient* p_ptr;
};

#endif /* QBTOBJECTEXCHANGECLIENT_STUB_H_ */
