/*
 * QBtObjectExchangeClient_win32.cpp
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

#include "../QBtObjectExchangeClient_win32.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <QByteArray>
#include <QFile>

QBT_NAMESPACE_BEGIN

#define MAX_FTP_FOLDER_LIST 128
#define MAX_FILENAME    256

bool QBtObjectExchangeClientPrivate::isBusy = false;
QBtObjectExchangeClientPrivate* QBtObjectExchangeClientPrivate::thisPtr = NULL;
QList<QBtRemoteFileInfo*>* QBtObjectExchangeClientPrivate::files = NULL;

QString QBtObjectExchangeClientPrivate::currentWorkingDirectory;

QBtObjectExchangeClientPrivate::QBtObjectExchangeClientPrivate(QBtObjectExchangeClient* publicClass,QObject* parent) :
	QObject(parent), p_ptr(publicClass), connectionHandle(BTSDK_INVALID_HANDLE), server(NULL), connectingService(NULL),
	maxFileNameSize(256)
{
	InitBthSdk();
	thisPtr = this;
}

QBtObjectExchangeClientPrivate::~QBtObjectExchangeClientPrivate()
{
	Disconnect();
	DeinitBthSdk();
	
	SafeDelete(server);
	SafeDelete(connectingService);
}

/**
* ConnectToServer
* Connect to the server
* @param remoteDevice the remote server to connect to
* @param remoteServive the remote service of the server
*/
void QBtObjectExchangeClientPrivate::ConnectToServer(const QBtDevice& remoteDevice, const QBtService& remoteService)
{
	//check
	if( !remoteDevice.getAddress().isValid())
	{
		emit p_ptr->error(QBtObjectExchangeClient::OBEXClientNoSelectedDevice);
		return;
	}
	if( remoteService.getClass()  == QBtUuid (QBtConstants::UndefinedClass) &&
		remoteService.getHandle() == 0)
	{
		emit p_ptr->error(QBtObjectExchangeClient::OBEXClientNoSelectedService);
		return;
	}
	
	server = new QBtDevice(remoteDevice);
	connectingService = new QBtService(remoteService);
	
	BTDEVHDL devHandle = GetDeviceHandle(server->getAddress());

	BTINT32 result = BTSDK_FALSE;

	if(connectionHandle != BTSDK_INVALID_HANDLE)
		result = Btsdk_Connect(connectingService->getHandle(), 0, &connectionHandle);
	else
		result = Btsdk_ConnectEx(devHandle, connectingService->getClass().get(), 0, &connectionHandle);

	if(result != BTSDK_OK)
		emit p_ptr->error(QBtObjectExchangeClient::OBEXClientConnectionError);
	else
		emit p_ptr->connectedToServer();
}

/**
* Disconnect
* Disconnect from the remote machine, by sending an
* OBEX disconnect, and closing the transport on (and
* regardless of) response from the server.
*/
void QBtObjectExchangeClientPrivate::Disconnect()
{
	if (connectionHandle != BTSDK_INVALID_HANDLE)
	{
		BTINT32 result = BTSDK_FALSE;
		result = Btsdk_Disconnect(connectionHandle);
		if(result != BTSDK_OK)
			emit p_ptr->error(QBtObjectExchangeClient::OBEXClientConnectionError);
		else
			emit p_ptr->disconnectedFromServer();
	}
}

/**
* SendFile
* Send a file to a service on a remote machine
*/
void QBtObjectExchangeClientPrivate::SendFile(const QString& fileName)
{
	if (connectionHandle == BTSDK_INVALID_HANDLE)
	{	
		emit p_ptr->error(QBtObjectExchangeClient::OBEXClientDisconnected);
		return;
	}

	WIN32_FIND_DATA pFindData;
	HANDLE hFile;
	BTUINT32 iErrorCode;
	
	//in case QFileDialog is used (or an address is given in the following format), 
	// all '/' are changed to  '\'.
	QString fileNameEdited = fileName;
	fileNameEdited.replace("/", "\\");

	QString  fileNamePath = fileNameEdited.left( fileNameEdited.lastIndexOf("\\") );


//	SetPath("");
//	SetPath(fileNamePath);

//	ZeroMemory(ucCurrentLocalPath, BTSDK_PATH_MAXLENGTH);
//	strcpy((char*)ucCurrentLocalPath, (char*)localFilePath);

	Btsdk_FTPRegisterStatusCallback4ThirdParty(connectionHandle, 
											&QBtObjectExchangeClientPrivate::FTPStatusCallback);
											
	hFile = FindFirstFile(fileNameEdited.utf16(),&pFindData);

	QString fileNameWStr = QString::fromUtf16(pFindData.cFileName);

	iErrorCode = Btsdk_FTPPutFile(connectionHandle, 
									(BTUINT8*)fileNameEdited.toUtf8().constData(),
									(BTUINT8*)fileNameWStr.toUtf8().constData());
		
	Btsdk_FTPRegisterStatusCallback4ThirdParty(connectionHandle, NULL);

	if(iErrorCode == BTSDK_OK)
		emit p_ptr->objectSent();
	else
		emit p_ptr->error(QBtObjectExchangeClient::OBEXClientSendError);
}

/**
* SendData
* Send a byte array to a service on a remote machine
*/
void QBtObjectExchangeClientPrivate::SendData(const QByteArray& /*data*/, const QString& /*bufferName*/)
{
	return;
}

/**
* GetFile
* 
* Request from the server to GET the file defined in the argument
*/
void QBtObjectExchangeClientPrivate::GetFile(const QString& localPath, const QString& remoteFileNameFull)
{
	if (connectionHandle == BTSDK_INVALID_HANDLE)
		return;

	//save current working directory to restore it after operation
	QString cwd = GetRemoteWorkingDirectory();

	int slashPosition = remoteFileNameFull.lastIndexOf("\\");

	QString localPathStr = localPath;
	QString remoteFilePath = remoteFileNameFull.left(slashPosition+1);
	QString remoteFileName = remoteFileNameFull.right(remoteFileNameFull.size() - slashPosition - 1);

	BTUINT32 iErrorCode;

	Btsdk_FTPRegisterStatusCallback4ThirdParty(connectionHandle, &QBtObjectExchangeClientPrivate::FTPStatusCallback);	

	// go to directory that contains the file
	if(remoteFilePath != currentWorkingDirectory)
	{
		SetPath("");
		SetPath(remoteFilePath);
	}
	
	//////////////////////////////////////////////////////////////////////////
	if(localPathStr.lastIndexOf("\\") != localPathStr.size() -1)
		localPathStr.append("\\");

	localPathStr += remoteFileName;
	//////////////////////////////////////////////////////////////////////////

	BTUINT8 remoteFile[MAX_FILENAME] = {0};
	BTUINT8 local[MAX_FILENAME] = {0};

	memcpy((char*)remoteFile, remoteFileName.toUtf8().data(), remoteFileName.size());
	memcpy((char*)local, localPathStr.toUtf8().data(), localPathStr.size());
	
	iErrorCode = Btsdk_FTPGetFile(connectionHandle, 
								remoteFile, 
								local);

	Btsdk_FTPRegisterStatusCallback4ThirdParty(connectionHandle, NULL);

	if(iErrorCode == BTSDK_OK)
		emit p_ptr->fileReceived(QString(localPathStr));
	else
		emit p_ptr->error(QBtObjectExchangeClient::OBEXClientReceiveError);

	//restore current working directory to the one before the operation starts
	SetPath(cwd);
		
	return;
}

/**
* GetByteBuffer()
* 
* Request from the server to GET the data buffer defined in the argument
*/
void QBtObjectExchangeClientPrivate::GetByteBuffer(const QString& /*dataName*/)
{
	return;
}

/**
* Abort
* Send the OBEX aborts command to the remote machine
*/
void QBtObjectExchangeClientPrivate::Abort()
{
	if(isBusy)
		Btsdk_FTPCancelTransfer(connectionHandle);
}

/**
* SetPath()
* Set the current path of the remote device OBEX session.
*/
bool QBtObjectExchangeClientPrivate::SetPath (const QString & path)
{
	if (connectionHandle == BTSDK_INVALID_HANDLE)
	{
		emit p_ptr->error(QBtObjectExchangeClient::OBEXClientDisconnected);
		return false;
	}

	BTINT32 iErrorCode;

	if(path == "..")
	{
		iErrorCode = Btsdk_FTPBackDir(connectionHandle);
		return (iErrorCode == BTSDK_OK);
	}


	QString pathEdited = path;
	if(pathEdited[0] != QChar('\\'))
		pathEdited.prepend("\\");

	// first try if file is in relative path form
	iErrorCode = Btsdk_FTPSetRmtDir(connectionHandle, (BTUINT8*)pathEdited.toUtf8().constData());

	if(iErrorCode != BTSDK_OK)
	{
		// then try as absolute path, going first to root path and then setting 
		// the path given as argument
		Btsdk_FTPSetRmtDir(connectionHandle, NULL);
		iErrorCode = Btsdk_FTPSetRmtDir(connectionHandle, (BTUINT8*)pathEdited.toUtf8().constData());
	}

	if(iErrorCode == BTSDK_OK)
	{
		QString remotePath(GetRemoteWorkingDirectory());
		emit p_ptr->remotePathSet(remotePath);
		return true;
	}
	else
	{
		emit p_ptr->error(QBtObjectExchangeClient::OBEXClientUnableToSetPath);
		return false;
	}
}

/**
* IsConnected
* @return true if the client is connected
*/
bool QBtObjectExchangeClientPrivate::IsConnected()
{
	return (connectionHandle != BTSDK_INVALID_HANDLE);
}

/**
* IsBusy
* @return true if the client is performing some operation.
*/
bool QBtObjectExchangeClientPrivate::IsBusy()
{
	return isBusy;
}

QString QBtObjectExchangeClientPrivate::GetRemoteWorkingDirectory()
{
	if (connectionHandle == BTSDK_INVALID_HANDLE)
	{
		emit p_ptr->error(QBtObjectExchangeClient::OBEXClientConnectionError);
		return QString("");
	}

	BTUINT8 remoteCurrentDir[MAX_FILENAME];
	BTINT32 result = BTSDK_FALSE;
	
	ZeroMemory(remoteCurrentDir, MAX_FILENAME);
	
	result = Btsdk_FTPGetRmtDir(connectionHandle, remoteCurrentDir);

	if(result == BTSDK_OK)
		return QString((char*)remoteCurrentDir);
	else
		return "";
}

QList<QBtRemoteFileInfo*> QBtObjectExchangeClientPrivate::InitiateFolderBrowsing(const QString folderPath)
{
	BTINT32 result = BTSDK_FALSE;
	QString folderPathStr = folderPath;
	QString currentdir(GetRemoteWorkingDirectory());

	currentWorkingDirectory = currentdir;

	if (connectionHandle == BTSDK_INVALID_HANDLE)	
	{
		emit p_ptr->error(QBtObjectExchangeClient::OBEXClientConnectionError);
		return QList<QBtRemoteFileInfo*>();
	}

	if(folderPath == "")
		folderPathStr = currentdir;

	SafeDelete(files);
	files = new QList<QBtRemoteFileInfo*>();

	if(folderPathStr == currentdir)
	{
		int slashPos = folderPathStr.lastIndexOf("\\");
		if(slashPos == folderPathStr.size()-1)
		{
			folderPathStr.resize(folderPathStr.size()-1);
			slashPos = folderPathStr.lastIndexOf("\\");
		}

		QString folderName = folderPathStr.right(folderPathStr.size() - slashPos - 1);
		currentWorkingDirectory = folderPathStr;

		result = Btsdk_FTPBrowseFolder(connectionHandle, (BTUINT8*)folderName.toAscii().data(), &QBtObjectExchangeClientPrivate::FTPBrowsingCallback, FTP_OP_REFRESH);
	}
	else
	{
		if(currentWorkingDirectory.size() != 1)
			currentWorkingDirectory += "\\";
		currentWorkingDirectory += folderPathStr;

		result = Btsdk_FTPBrowseFolder(connectionHandle, (BTUINT8*)folderPathStr.toAscii().data(), &QBtObjectExchangeClientPrivate::FTPBrowsingCallback, FTP_OP_NEXT);
	}

	//if not empty then it means that there was some error
	if (!(result == 0X6a4))	
		emit p_ptr->error(QBtObjectExchangeClient::OBEXClientBrowseError);

	return QList<QBtRemoteFileInfo*>(*files);
}

QList<QBtRemoteFileInfo*> QBtObjectExchangeClientPrivate::locateFiles(QRegExp* regex, QString folder)
{
	static int refCounter=0;
	QString cwd;
	if(!refCounter++)
	{
		//save current working directory to restore it after operation
		cwd = GetRemoteWorkingDirectory();
		selectedFiles.clear();
	}

	QList<QBtRemoteFileInfo*>& results = InitiateFolderBrowsing(folder);

	if(regex == NULL)
	{
		regex = new QRegExp("*");
		regex->setPatternSyntax(QRegExp::Wildcard);
		regex->setCaseSensitivity(Qt::CaseInsensitive);
	}

	for(int i=0; i<results.size(); i++)
	{
		if(results[i]->isDir)
		{
			locateFiles(regex, results[i]->fileName);
			SetPath("..");
		}
		else{
			if(regex == NULL)
				return QList<QBtRemoteFileInfo*>();

			if (results[i]->fileName.contains(*regex))
			{
				//currently adds all the non directory files in
				selectedFiles.append(results[i]);
			}
		}
	}

	if(!--refCounter)
	{
		//restore current working directory to the one before the operation starts
		SetPath(cwd);
		return selectedFiles;
	}
	else
		return QList<QBtRemoteFileInfo*>();
}

void QBtObjectExchangeClientPrivate::batchFileRetrieval(const QList<QBtRemoteFileInfo*>& files, 
																 const QString destinationFolder,
																 bool retrieveOnlyNewFiles)
{
	QList<QBtRemoteFileInfo*> filesEdited;
	QString destFolderEdited = destinationFolder;

	if(retrieveOnlyNewFiles)
	{
		for(int i=0; i<files.size(); i++)
		{
			if(destFolderEdited.lastIndexOf("\\") != destFolderEdited.size() -1)
				destFolderEdited.append("\\");

			QString fileLocalAbsolute = destFolderEdited + files[i]->fileName;
			//check local file system if file is already there
			if(!QFile(fileLocalAbsolute).exists())
			{
				filesEdited.append(files[i]);
				cout << "File: " << files[i]->fileName.toAscii().data() << " queued for download." << endl;
			}
		}
	}

	if(retrieveOnlyNewFiles)
		for(int i=0; i<filesEdited.size(); i++)
			GetFile(destinationFolder, filesEdited[i]->absolutePath);
	else
		for(int i=0; i<files.size(); i++)
			GetFile(destinationFolder, files[i]->absolutePath);
}

/************************************************************************/
/*                     Transfer info callback                           */
/************************************************************************/
void QBtObjectExchangeClientPrivate::FTPStatusCallback(UCHAR ucFirst, 
					UCHAR ucLast, UCHAR* ucFileName, DWORD dwFilesize, DWORD dwCursize)
{
	static BTUINT32 s_TotalFileSize;
	static BTUINT32 s_CurrentFileSize;

	if (1 == ucFirst)
	{
		s_TotalFileSize = dwFilesize;
		s_CurrentFileSize = 0;
		
		isBusy = true;
	}
	
	printf("*******It is transfering file %s, and current size = %d****\n",
							ucFileName,s_CurrentFileSize += dwCursize);
		    
	if (1 == ucLast)
	{
		printf("*******It has finished transfering file %s,and total size = %d ****\n",
			   ucFileName,s_TotalFileSize);
		
		isBusy = false;
	}
}

void QBtObjectExchangeClientPrivate::FTPBrowsingCallback(BTUINT8 *pFileInfo)
{	
	QBtRemoteFileInfo file;

	WIN32_FIND_DATA *pFindData = NULL;

	if (NULL == pFileInfo) return;

	pFindData = (WIN32_FIND_DATA *)pFileInfo;	
	file.fileName = QString::fromUtf8((char*)pFindData->cFileName);
	file.size = pFindData->nFileSizeLow;
	file.type = pFindData->dwFileAttributes;
	file.isDir = (pFindData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	file.path = currentWorkingDirectory;

	file.creationTime = convertToQDate(pFindData->ftCreationTime);
	file.lastAccessTime = convertToQDate(pFindData->ftLastAccessTime);
	file.lastWriteTime = convertToQDate(pFindData->ftLastWriteTime);

	if(files)
		files->append(new QBtRemoteFileInfo(file));
 
	Btsdk_FreeMemory(pFileInfo);
}

QDate QBtObjectExchangeClientPrivate::convertToQDate(FILETIME& time)
{
	SYSTEMTIME sysTime;
	FileTimeToSystemTime( &time, &sysTime);

	QDate qdate(sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	return qdate;
}

QBT_NAMESPACE_END