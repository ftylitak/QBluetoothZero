#include "remotebrowser.h"
#include <iostream>
#include <iomanip>
using namespace std;

RemoteBrowser::RemoteBrowser(QBtAddress& address, QObject *parent) :
    QObject(parent), remoteDevice(), servDisc(this)
{
    QBluetooth::registerTypes();

    remoteDevice.setAddress(address);
    connect(&servDisc, SIGNAL(newServiceFound (const QBtDevice &, const QBtService &)),
            this, SLOT(ftpServiceFound(const QBtDevice &, const QBtService &)));

    connect(&servDisc, SIGNAL(discoveryStarted ()),
            this, SLOT(serviceDiscoveryStarted()));

    connect(&servDisc, SIGNAL(discoveryStopped ()),
            this, SLOT(serviceDiscoveryStopped()));

    connect(&servDisc, SIGNAL(error (QBtServiceDiscoverer::ServiceDiscoveryError)),
            this, SLOT(onError(QBtServiceDiscoverer::ServiceDiscoveryError)));
}

RemoteBrowser::~RemoteBrowser()
{
    SafeDelete(client);
}

void RemoteBrowser::initializeConnectionData()
{
    cout << "Starting Service Discovery on: " << remoteDevice.getAddress().toString().toAscii().data() << endl;
    servDisc.startDiscovery(remoteDevice, QBtUuid(QBtConstants::OBEXFileTransfer));
}

void RemoteBrowser::ftpServiceFound(const QBtDevice &/*targetDevice*/, const QBtService &service)
{
    servDisc.stopDiscovery();
    cout << "Service found: " << service.getName().toAscii().data()
         << ", Uuid: " << service.getClass().toString().toAscii().data()
         << endl;
    remoteFtpService = QBtService(service);
}

void RemoteBrowser::serviceDiscoveryStarted()
{
    cout << "Service discovery started" << endl;
}

void RemoteBrowser::serviceDiscoveryStopped()
{
    cout << "Service discovery stopped" << endl;
}

void RemoteBrowser::onError(QBtServiceDiscoverer::ServiceDiscoveryError error)
{
    cout << "Error discovering services: " << error << endl;
}

void RemoteBrowser::connectToDevice()
{
    client = new QBtObjectExchangeClient(this);

    connect(client, SIGNAL(error (QBtObjectExchangeClient::ErrorCode)),
            this, SLOT(onError (QBtObjectExchangeClient::ErrorCode)));

    connect(client, SIGNAL(connectedToServer ()),
            this, SLOT(onConnectedToServer ()));

    connect(client, SIGNAL(disconnectedFromServer ()),
            this, SLOT(onDisconnectedFromServer ()));

    connect(client, SIGNAL(objectSent ()),
            this, SLOT(onObjectSent ()));

    connect(client, SIGNAL(fileReceived (const QString)),
            this, SLOT(onFileReceived (const QString)));

    connect(client, SIGNAL(dataReceived (const QByteArray)),
            this, SLOT(onDataReceived (const QByteArray)));

    connect(client, SIGNAL(remotePathSet (const QString )),
            this, SLOT(onRemotePathSet (const QString)));

    connect(client, SIGNAL(folderBrowsingResultElement(const QBtRemoteFileInfo&)),
            this, SLOT(onFolderBrowsingResultElement(const QBtRemoteFileInfo&)));

    connect(client, SIGNAL(fileReceived (const QString&)),
            this, SLOT(onFileReceived(const QString&)));

    client->connectToServer(remoteDevice, remoteFtpService);
}

QString RemoteBrowser::pwd()
{
    QString workingDir = client->getWorkingPath();
    //cout << "Working path: " << workingDir.toAscii().data() << endl;
    return workingDir;
}

void RemoteBrowser::cd(QString path)
{
    client->setPath(path);
}

QList<QBtRemoteFileInfo*> RemoteBrowser::ls(QString path)
{
    return client->initiateFolderBrowsing(path);
}

QList<QBtRemoteFileInfo*> RemoteBrowser::locateFiles(QString folder, QRegExp* regex, bool isRecursive)
{
    return client->locateFiles(regex, folder, isRecursive);
}

QHash<QBtRemoteFileInfo, bool> RemoteBrowser::batchFileRetrieval(const QList<QBtRemoteFileInfo*>& files, 
                                                                 const QString destinationFolder,
                                                                 bool retrieveOnlyNewFiles)
{
    client->batchFileRetrieval(files, destinationFolder, retrieveOnlyNewFiles);

    return QHash<QBtRemoteFileInfo, bool>();
}

void RemoteBrowser::receiveFile(const QString remoteFileAbsolutePath, const QString destinationFolder)
{
    client->getFile(remoteFileAbsolutePath, destinationFolder);
}

void RemoteBrowser::retrieveNewImages(QString remoteFolder, QString localFolder)
{
    cd(remoteFolder);
    QRegExp expression(".jpg$|.jpeg$|.png$|.bmp$");
    expression.setCaseSensitivity(Qt::CaseInsensitive);

    QList<QBtRemoteFileInfo*> images = locateFiles("", &expression);
    batchFileRetrieval(images, localFolder, true);
}

/************************************************************************/
/* Logging functions                                                    */
/************************************************************************/

void RemoteBrowser::printFileListInfo(QList<QBtRemoteFileInfo*>& list)
{
    for(int i=0; i< list.size(); i++)
        onFolderBrowsingResultElement(*list[i]);
}

void RemoteBrowser::onFolderBrowsingResultElement(const QBtRemoteFileInfo& file)
{
    cout << "\t" << file.absolutePath.toAscii().data() << "\t" << (file.isDir ? "D" : "_") << "\t" << file.size << "\t" << file.creationTime.toString("dd/MM/yyyy").toStdString() << endl;
}

void RemoteBrowser::disconnectFromDevice()
{
    client->disconnect();
}

void RemoteBrowser::onError (QBtObjectExchangeClient::ErrorCode /*code*/)
{
    //cout << "Error on FTP connection: " << code << endl;
}

void RemoteBrowser::onConnectedToServer ()
{
    cout << "Connected to FTP server" << endl;
}

void RemoteBrowser::onDisconnectedFromServer ()
{
    cout << "Disconnected from FTP server" << endl;
    //SafeDelete(client);
}

void RemoteBrowser::onObjectSent ()
{
    cout << "Object successfully sent" << endl;
}

void RemoteBrowser::onFileReceived (const QString& fileName)
{
    cout << "File received: " << fileName.toAscii().data() << endl;
}

void RemoteBrowser::onDataReceived (const QByteArray data)
{
    cout << "Data received, size: " << data.size() << endl;
}

void RemoteBrowser::onRemotePathSet (const QString pathName)
{
    //cout << "Remote path changed: " << pathName.toAscii().data() << endl;
}

bool RemoteBrowser::isConnected()
{
    if(client)
        return client->isConnected();
    else
        return false;
}
