#ifndef REMOTEBROWSER_H
#define REMOTEBROWSER_H

#include <QObject>
#include <QBluetooth.h>
#include <QList>
#include <QHash>
#include <QRegExp>

class RemoteBrowser : public QObject
{
    Q_OBJECT
public:
    explicit RemoteBrowser(QBtAddress& address, QObject *parent = 0);
    ~RemoteBrowser();

    ///////////////////////////////////////////////////////////////////////////
    ////			Service functions										///
    //////////////////////////////////////////////////////////////////////////

public:
    void initializeConnectionData();
    void connectToDevice();
    void disconnectFromDevice();
    QString pwd();
    void cd(QString path);
    QList<QBtRemoteFileInfo*> ls(QString path="");
    QList<QBtRemoteFileInfo*> locateFiles(QString folder="", QRegExp* regex=0, bool isRecursive = false);
    QHash<QBtRemoteFileInfo, bool> batchFileRetrieval(const QList<QBtRemoteFileInfo*>& filesfiles,
                                                      const QString destinationFolder,
                                                      bool retrieveOnlyNewFiles = false);

    void printFileListInfo(QList<QBtRemoteFileInfo*>& list);
    void receiveFile(const QString remoteFileAbsolutePath, const QString destinationFolder);
    void retrieveNewImages(QString remoteFolder, QString localFolder);

    bool isConnected();

signals:

public slots:
    void ftpServiceFound(const QBtDevice &targetDevice, const QBtService &service);
    void serviceDiscoveryStarted();
    void serviceDiscoveryStopped();
    void onError(QBtServiceDiscoverer::ServiceDiscoveryError error);

    void onError (QBtObjectExchangeClient::ErrorCode code);
    void onConnectedToServer ();
    void onDisconnectedFromServer ();
    void onObjectSent ();
    void onFileReceived (const QString& fileName);
    void onDataReceived (const QByteArray data);
    void onRemotePathSet (const QString pathName);

    void onFolderBrowsingResultElement(const QBtRemoteFileInfo& file);

private:
    QBtDevice remoteDevice;
    QBtService remoteFtpService;
    QBtServiceDiscoverer servDisc;
    QBtObjectExchangeClient* client;
    QList<QBtRemoteFileInfo*> images;
};

#endif // REMOTEBROWSER_H
