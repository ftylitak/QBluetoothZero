/****************************************************************************
 **
 ** Trolltech hereby grants a license to use the Qt/Eclipse Integration
 ** plug-in (the software contained herein), in binary form, solely for the
 ** purpose of creating code to be used with Trolltech's Qt software.
 **
 ** Qt Designer is licensed under the terms of the GNU General Public
 ** License versions 2.0 and 3.0 ("GPL License"). Trolltech offers users the
 ** right to use certain no GPL licensed software under the terms of its GPL
 ** Exception version 1.2 (http://trolltech.com/products/qt/gplexception).
 **
 ** THIS SOFTWARE IS PROVIDED BY TROLLTECH AND ITS CONTRIBUTORS (IF ANY) "AS
 ** IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 ** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 ** PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 ** OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 ** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 ** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 ** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 ** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 ** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 ** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 **
 ** Since we now have the GPL exception I think that the "special exception
 ** is no longer needed. The license text proposed above (other than the
 ** special exception portion of it) is the BSD license and we have added
 ** the BSD license as a permissible license under the exception.
 **
 ****************************************************************************/

#include "QuteMessenger.h"
#include <QRect>
#include <QMenu>
#include <QFileDialog>
#include <QMovie>
#include <QBtAuxFunctions.h>

/*
#ifdef Q_OS_SYMBIAN // used only to hide status pane
#include <eikspane.h>
#include <aknappui.h>
#include <avkon.rsg>
#include <EIKENV.H>
#include <coemain.h>

#endif
*/
QuteMessenger::QuteMessenger(QWidget *parent) :
    QMainWindow(parent), previousSelectedTab(0), rfcommServer(NULL), devDisc(NULL), serviceDisc(
        NULL), obexClient(NULL), dialog(NULL), obexDialog(NULL)
{
    /*
     #ifdef Q_OS_SYMBIAN
     CEikStatusPane* statusPane = STATIC_CAST( CAknAppUi*, CEikonEnv::Static()->EikAppUi())->StatusPane();
     statusPane->MakeVisible(EFalse);
     #endif*/

    int deviceYourClass = qRegisterMetaType<QBtDevice> ("QBtDevice");
    int addressYourClass = qRegisterMetaType<QBtAddress> ("QBtAddress");

    ui.setupUi(this);

    //dialog = new QProgressDialog(ui.deviceListWidget);

    CreateActions();
    SetupMenu(true);

    //setup devSearchButton signal handler
    connect(ui.devSearchButton, SIGNAL(clicked()), this, SLOT(startDeviceDiscovery()));

    connect(ui.deviceListWidget, SIGNAL(itemActivated(QListWidgetItem*)), this,
            SLOT(deviceSelected(QListWidgetItem*)));

    connect(ui.deviceListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this,
            SLOT(deviceSelected(QListWidgetItem*)));

    connect(ui.tabWidget, SIGNAL( tabCloseRequested ( int )), this, SLOT(closeCurrentTab()));

    //connect(ui.)

    InitializeBluetooth();

    this->setWindowFlags(Qt::WindowSoftkeysVisibleHint);
    this->showFullScreen();

    //    QRect screenSize = QApplication::desktop()->screenGeometry();
    //    this->setGeometry(25,25, screenSize.width()/2, screenSize.height()/2);
}

QuteMessenger::~QuteMessenger()
{
    for (int i = 0; i < chatTabs.size(); i++)
        SafeDelete(chatTabs[i]);

    if (rfcommServer) {
        disconnect(rfcommServer, SIGNAL(clientDisconnected()));
        disconnect(rfcommServer, SIGNAL(clientConnected(QBtAddress)));
        delete rfcommServer;
    }
    if (devDisc) {
        disconnect(devDisc, SIGNAL(newDeviceFound(QBtDevice)));
        disconnect(devDisc, SIGNAL(discoveryStopped()));
        delete devDisc;
    }
    if (serviceDisc)
        delete serviceDisc;

}

void QuteMessenger::paintEvent(QPaintEvent* event)
{

#ifdef Q_OS_SYMBIAN
    static int savedWidth = 0, savedHeight = 0;
    QRect screenSize = QApplication::desktop()->screenGeometry();

    if ((savedWidth == 0 && savedHeight == 0) || (savedWidth != screenSize.width() || savedHeight
                                                  != screenSize.height())) {
        this->setGeometry(0, 0, screenSize.width(), screenSize.height());
        savedWidth = screenSize.width();
        savedHeight = screenSize.height();
    }
#endif
}

void QuteMessenger::CreateActions()
{
    discoverDev = new QAction(QString(tr("Discover devices")), this);
    discoverDev->setSoftKeyRole(QAction::SelectSoftKey);
    connect(discoverDev, SIGNAL(triggered()), this, SLOT(startDeviceDiscovery()));

    sendFile = new QAction(QString(tr("Send file")),this);
    sendFile->setSoftKeyRole(QAction::SelectSoftKey);
    connect(sendFile, SIGNAL(triggered()), this, SLOT(sendFileToClient()));

    startChat = new QAction(QString(tr("Start chat")),this);
    startChat->setSoftKeyRole(QAction::SelectSoftKey);
    connect(startChat, SIGNAL(triggered()), this, SLOT(startChatReport()));
}

void QuteMessenger::SetupMenu(bool isInitial)
{
    menuBar()->clear();
    if (isInitial) {
        menuBar()->addAction(discoverDev);
        update();
    }
    else {
        menuBar()->addAction(startChat);
        menuBar()->addAction(sendFile);
    }
}

void QuteMessenger::SaveSelectedDevice()
{
    //Get the selected device
    for (int i = 0; i < foundDevices.size(); i++) {
        if (foundDevices[i].getName() == selectedDeviceName) {
            deviceQueriedForServices = foundDevices[i];
            break;
        }
    }
}

void QuteMessenger::closeCurrentTab()
{
    QChatWidget* closingTab = (QChatWidget*) ui.tabWidget->currentWidget();

    if (chatTabs.indexOf(closingTab) == -1)
        return;

    chatTabs.removeAt(chatTabs.indexOf(closingTab));
    ui.tabWidget->removeTab(ui.tabWidget->currentIndex());

    if (closingTab)
        delete closingTab;
}

void QuteMessenger::InitializeBluetooth()
{
    // power on bluetooth
    QBtLocalDevice::askUserTurnOnBtPower();
    
    const QBtUuid uid = QBtUuid(QBtConstants::SerialPort);

    // start rfcomm server
    rfcommServerServiceName = QString("Messenger Protocol ");
    rfcommServerServiceName += QBtLocalDevice::getLocalDeviceName();

    rfcommServer = new QBtSerialPortServer(this);
    rfcommServer->startServer(uid, rfcommServerServiceName);


    connect(rfcommServer, SIGNAL(clientDisconnected()),
            this, SLOT(restartSerialPortServer()));

    connect(rfcommServer, SIGNAL(clientConnected(const QBtAddress &)),
            this, SLOT(createNewTab(const QBtAddress &)));

    //create an instance of BT device discoverer
    devDisc = new QBtDeviceDiscoverer(this);

    //service discoverer
    serviceDisc = new QBtServiceDiscoverer(this);
}

void QuteMessenger::restartSerialPortServer()
{
    const QBtUuid uid = QBtUuid(QBtConstants::SerialPort);
    rfcommServer->startServer(uid, rfcommServerServiceName);
}

void QuteMessenger::createNewTab(const QBtAddress & address)
{
    QChatWidget* tmpChat;
    tmpChat = new QChatWidgetServer(this);
    tmpChat->SetName(address.toString());

    ((QChatWidgetServer*) tmpChat)->SetDiscoverer(devDisc);

    ((QChatWidgetServer*) tmpChat)->SetServer(rfcommServer);
    connect(tmpChat, SIGNAL(tabNameChanged(QString, QChatWidget*)), this,
            SLOT(tabNameChangedReport(QString, QChatWidget*)));

    ui.tabWidget->addTab(tmpChat, "Chat");
    chatTabs.append(tmpChat);
}

void QuteMessenger::tabNameChangedReport(QString newName, QChatWidget* tab)
{
    int index = ui.tabWidget->indexOf(tab);

    //if not found
    if (index == -1)
        return;

    ui.tabWidget->setTabText(index, tab->GetName());
}

/***************************************************************
 *			Device discovery related functions
 ***************************************************************/

void QuteMessenger::startDeviceDiscovery()
{
    SetupMenu(true);
    if (devDisc) {
        ui.deviceListWidget->clear();
        foundDevices.clear();
        connect(devDisc, SIGNAL(newDeviceFound(QBtDevice)), this,
                SLOT(populateDeviceList(QBtDevice)));
        connect(devDisc, SIGNAL(discoveryStopped()), this, SLOT(deviceDiscoveryCompleteReport()));
        devDisc->startDiscovery();

        dialog = new QProgressDialog("Searching devices...", "Stop", 0, 0, this);
        dialog->setWindowModality(Qt::WindowModal);
        connect(dialog, SIGNAL(canceled()), this, SLOT(deviceDiscoveryCompleteReport()));
        dialog->setBar(NULL);

        dialog->show();
    }
}

void QuteMessenger::populateDeviceList(QBtDevice newDevice)
{
    ui.deviceListWidget->addItem(newDevice.getName());
    foundDevices.append(newDevice);
}

void QuteMessenger::deviceDiscoveryCompleteReport()
{
    disconnect(devDisc, SIGNAL(newDeviceFound(QBtDevice)), this,
               SLOT(populateDeviceList(QBtDevice)));
    disconnect(devDisc, SIGNAL(discoveryStopped()), this, SLOT(deviceDiscoveryCompleteReport()));

    if (dialog) {
        dialog->hide();
        delete dialog;
    }
}

void QuteMessenger::deviceSelected(QListWidgetItem* item)
{
    SetupMenu(false);
    selectedDeviceName = item->text();
}

/***************************************************************
 *			Send file functions (OBEX related)
 ***************************************************************/
void QuteMessenger::sendFileToClient()
{
    //select file from file system
    selectedFileToSend = QFileDialog::getOpenFileName(this, QString(tr("Select File")), "C:\\", tr(
                                                          "Any file (*.*)"));
    if (selectedFileToSend == "")
        return;

    obexDialog = new QProgressDialog(QString(tr("Connecting to device...")), QString(tr("Abort")), 0, 0);
    obexDialog->setWindowModality(Qt::WindowModal);
    connect(obexDialog, SIGNAL(canceled()), this, SLOT(obexOperationCanceld()));
    obexDialog->show();

    //search remote device for an OBEX compatible service
    SaveSelectedDevice();

    // if bluetooth address is uninitialized
    if (deviceQueriedForServices.getAddress().toString() == QBtAddress().toString()) {
        obexDialog->hide();
        obexOperationCanceld();
        SafeDelete(obexDialog);
        return;
    }

    connect(serviceDisc, SIGNAL(newServiceFound(const QBtDevice&, const QBtService&)), this,
            SLOT(newServiceFound(const QBtDevice&, const QBtService&)));

    const QBtUuid uid(QBtConstants::OBEXObjectPush);
    serviceDisc->startDiscovery(deviceQueriedForServices, uid);
}

void QuteMessenger::newServiceFound(const QBtDevice& dev, const QBtService& serv)
{
    //since we need only the first available service with the given ClassID
    //when the first service is reported, the service discovery stops
    disconnect(serviceDisc, SIGNAL(newServiceFound(const QBtDevice&, const QBtService&)), this,
               SLOT(newServiceFound(const QBtDevice&, const QBtService&)));

    qDebug() << "Service to connect: " << serv.getName();
    qDebug() << "UUID: " << serv.getClass().get();
    qDebug() << "Dev: " << dev.getName();
    qDebug() << "Dev Addr: " << dev.getAddress().toString();

    if(obexClient)
    {
        delete obexClient;
        obexClient = NULL;
    }

    obexClient = new QBtObjectExchangeClient(this);

    connect(obexClient, SIGNAL(connectedToServer()), this, SLOT(connectedToRemoteOBEXServer()));
    connect(obexClient, SIGNAL(objectSent()), this, SLOT(fileSent()));
    connect(obexClient, SIGNAL(error (QBtObjectExchangeClient::ErrorCode)),
            this, SLOT(reportObexError(QBtObjectExchangeClient::ErrorCode)) );

    selectedService = serv;

    obexClient->connectToServer(deviceQueriedForServices, selectedService);
}

void QuteMessenger::reportObexError(QBtObjectExchangeClient::ErrorCode error)
{
    qDebug() << "Error: " << error;
}

void QuteMessenger::connectedToRemoteOBEXServer()
{
    if (obexClient) {
        disconnect(obexClient, SIGNAL(connectedToServer()), this,
                   SLOT(connectedToRemoteOBEXServer()));
    }

    obexDialog->hide();
    SafeDelete(obexDialog);

    obexDialog = new QProgressDialog(QString(tr("Sending File...")), QString(tr("Stop")), 0, 0);
    obexDialog->setWindowModality(Qt::WindowModal);
    connect(obexDialog, SIGNAL(canceled()), this, SLOT(obexOperationCanceld()));
    obexDialog->show();

    obexClient->putFile(selectedFileToSend);
}

void QuteMessenger::fileSent()
{
    if(obexClient)
    {
        obexClient->disconnect();
        disconnect(obexClient, SIGNAL(objectSent()), this, SLOT(fileSent()));
    }

    if(obexDialog)
    {
        obexDialog->hide();
        SafeDelete(obexDialog);
    }
}

void QuteMessenger::obexOperationCanceld()
{
    if (serviceDisc && serviceDisc->isBusy())
        serviceDisc->stopDiscovery();

    fileSent();
}

/*************************************************************
 *  	Start chat from the client side
 *************************************************************/
void QuteMessenger::startChatReport()
{
    SaveSelectedDevice();

    //////////////////////////////////////////////

    //////////////////////////////////////////////

    connect(serviceDisc, SIGNAL(newServiceFound(const QBtDevice&, const QBtService&)), this,
            SLOT(newSerialServiceFound(const QBtDevice&, const QBtService&)));

    connect(serviceDisc, SIGNAL(discoveryStopped ()),
            this, SLOT(unregisterServiceDiscoveryConnection()));

    const QBtUuid uid(QBtConstants::SerialPort);
    serviceDisc->startDiscovery(deviceQueriedForServices, uid);
}

void QuteMessenger::unregisterServiceDiscoveryConnection()
{
    disconnect(serviceDisc, SIGNAL(newServiceFound(const QBtDevice&, const QBtService&)),
               this, SLOT(newSerialServiceFound(const QBtDevice&, const QBtService&)));
    disconnect(this, SIGNAL(serialParamRetreived(QBtDevice, QBtService)));
}

void QuteMessenger::newSerialServiceFound(const QBtDevice& dev, const QBtService& serv)
{
    QString exprectedServiceName("Messenger Protocol ");
    exprectedServiceName += dev.getName();

    qDebug() << exprectedServiceName;
    qDebug() << serv.getName();

    if (QString::compare(exprectedServiceName, serv.getName()) == 0)
    {
        serviceDisc->stopDiscovery();
        selectedService = serv;

        QChatWidgetClient* tmpChat;
        tmpChat = new QChatWidgetClient(this);
        tmpChat->SetName(deviceQueriedForServices.getName());

        ui.tabWidget->addTab(tmpChat, deviceQueriedForServices.getName());
        chatTabs.append((QChatWidget*) tmpChat);

        connect(this, SIGNAL(serialParamRetreived(QBtDevice, QBtService)),
                tmpChat, SLOT(setParameters(QBtDevice, QBtService)));

        emit serialParamRetreived(dev, serv);
    }
}

