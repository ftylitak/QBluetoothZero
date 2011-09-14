/*
 * QBtObjectExchangeClient_win32.h
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

#ifndef QBTOBJECTEXCHANGECLIENT_WIN32_H_
#define QBTOBJECTEXCHANGECLIENT_WIN32_H_

#include <QBtObjectExchangeClient.h>
#include <QBtAuxFunctions.h>
#include <QList>

QBT_NAMESPACE_BEGIN

class QBtObjectExchangeClientPrivate : public QObject
{

Q_OBJECT

public:

    QBtObjectExchangeClientPrivate(QBtObjectExchangeClient* publicClass, QObject* parent=0);
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
    bool SetPath (const QString & path);

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

	/**
	 *	InitiateFolderBrowsing()
	 *
	 *	Browse the files of a selected folder. 
	 *
	 *  @param folder The folder path must either be absolute (e.g. \E:\Images), or it must be the name of the folder
	 *  you are going to browse as long as the folder is inside the current working directory of yours.
	 *  
	 *  @return QList<QBtRemoteFileInfo*> a list of the files/folders found and their attributes
	 */
	QList<QBtRemoteFileInfo*> InitiateFolderBrowsing(const QString folderPath="");

	/**
	 * GetRemoteWorkingDirectory
	 * 
	 * Return as QString holding the absolute path of the current working directory
	 */
	QString GetRemoteWorkingDirectory();

	/**
	 *	locateFiles
	 *
	 *	Locate files/folders that comply to the regex passed as arguments. For example can be used to isolate 
	 *	files of specific type.
	 *
	 *	@param regex The regex that describes the files that are needed to be selected. If this parameter is not set, the default
	 *	operation is to select all the files in the specified folder.
	 *
	 *	@param folder The folder path must either be absolute (e.g. \E:\Images), or it must be the name of the folder
	 *  you are going to browse as long as the folder is inside the current working directory of yours. If this parameter is not set, 
	 *	the default operation is to search in the current working directory.
	 */
	QList<QBtRemoteFileInfo*> locateFiles(QRegExp* regex=0, QString folder="");

	/**
	 *	batchFileRetrieval
	 *
	 *	Convenient method to retrieve multiple files in the row.
	 *
	 *	@param files The list of files to retrieve
	 *	@param destinationFolder The folder in the local file system where the files will be stored. The files are placed all
	 *	in that directory same directory so the structure in the remote file system is not preserved.
	 */
	void batchFileRetrieval(const QList<QBtRemoteFileInfo*>& files,
		const QString destinationFolder,
		bool retrieveOnlyNewFiles = false);


private:
    // Callback containing file transfer info
    static void FTPStatusCallback(UCHAR ucFirst,
                            UCHAR ucLast,
                            UCHAR* ucFileName,
                            DWORD dwFilesize,
                            DWORD dwCursize);
	static void FTPBrowsingCallback(BTUINT8 *pFileInfo);
	static QDate convertToQDate(FILETIME& time);

signals:
	void folderBrowsingResultElement(const QBtRemoteFileInfo& file);
	void browsingFinished(QString folder, QList<QBtRemoteFileInfo> resutls);

private:
    static bool isBusy;
    size_t maxFileNameSize;
    BTDEVHDL connectionHandle;
    QBtDevice* server;
    QBtService* connectingService;
	QList<QBtRemoteFileInfo*> selectedFiles;

    QBtObjectExchangeClient* p_ptr;

	static QBtObjectExchangeClientPrivate* thisPtr;
	static QList<QBtRemoteFileInfo*>* files;
	static QString currentWorkingDirectory;
};
QBT_NAMESPACE_END

#endif /* QBTOBJECTEXCHANGECLIENT_WIN32_H_ */
