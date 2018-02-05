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

#ifndef QUTEMESSENGER_H
#define QUTEMESSENGER_H

#include <QtGui>
#include <QBluetoothZero.h>
#include "ui_QuteMessenger.h"
#include "QChatWidgetServer.h"
#include "QChatWidgetClient.h"
#include <QList>
#include <QDialog>
#include <QProgressDialog.h>


#define DEFAULT_SEARCH_UI

class QuteMessenger : public QMainWindow
{
    Q_OBJECT

public:
    QuteMessenger(QWidget *parent = 0);
    ~QuteMessenger();

    void SetupMenu(bool isInitial);

protected:
    void paintEvent(QPaintEvent* event);

private:
    void InitializeBluetooth();
    void CreateActions();
    void SaveSelectedDevice();

private slots:
    void deviceSelected(QListWidgetItem* item);

    void closeCurrentTab();
    void restartSerialPortServer();
    void createNewTab(const QBtAddress & address);
    void tabNameChangedReport(QString newName, QChatWidget* tab);

    //device discoverer slots
    void startDeviceDiscovery();
    void populateDeviceList(QBtDevice newDevice);
    void deviceDiscoveryCompleteReport();

    //obex client slots
    void sendFileToClient();
    void newServiceFound(const QBtDevice& dev, const QBtService& serv);
    void connectedToRemoteOBEXServer();
    void fileSent();

    //start chat from the client side
    void startChatReport();
    void newSerialServiceFound(const QBtDevice& dev, const QBtService& serv);
    
    void obexOperationCanceld();
    void unregisterServiceDiscoveryConnection();

    void reportObexError(QBtObjectExchangeClient::ErrorCode error);

signals:
    void serialParamRetreived(QBtDevice dev, QBtService sesrv);

private:
    Ui::QuteMessengerClass ui;

    QMovie *donkey;

    QAction* discoverDev;
    QAction* sendFile;
    QAction* startChat;

    QList<QChatWidget*> chatTabs;

    int previousSelectedTab;

    //For bluetooth operation
    QBtDeviceDiscoverer* devDisc;
    QBtSerialPortServer* rfcommServer;
    QString rfcommServerServiceName;
    QList<QBtDevice> foundDevices;

    QBtObjectExchangeClient* obexClient;
    QBtServiceDiscoverer* serviceDisc;

    QString selectedDeviceName;
    QString selectedFileToSend;
    //
    QBtDevice deviceQueriedForServices;
    QBtService selectedService;

    QProgressDialog* dialog;
    
    QProgressDialog* obexDialog;
};

#endif // QUTEMESSENGER_H
