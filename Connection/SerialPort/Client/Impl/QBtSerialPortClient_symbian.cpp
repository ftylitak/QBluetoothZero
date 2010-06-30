/*
 * QBtSerialPortClient_symbian.cpp
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtSerialPortClient_symbian.h"
#include <QBtAuxFunctions.h>

QBtSerialPortClientPrivate* QBtSerialPortClientPrivate::NewL(QBtSerialPortClient* publicClass)
{
    QBtSerialPortClientPrivate* self = QBtSerialPortClientPrivate::NewLC(publicClass);
    CleanupStack::Pop(self);
    return self;
}


QBtSerialPortClientPrivate* QBtSerialPortClientPrivate::NewLC(QBtSerialPortClient* publicClass)
{
    QBtSerialPortClientPrivate* self = new (ELeave) QBtSerialPortClientPrivate(publicClass);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}


void QBtSerialPortClientPrivate::ConstructL()
{
    if(iSocketServ.Connect() != KErrNone)
        emit p_ptr->error(QBtSerialPortClient::BluetoothSPCUnavailable);
}


QBtSerialPortClientPrivate::QBtSerialPortClientPrivate(QBtSerialPortClient* publicClass):
            CActive(CActive::EPriorityStandard),
            iState(ENone),
            p_ptr(publicClass)
{
    CActiveScheduler::Add(this);
}


QBtSerialPortClientPrivate::~QBtSerialPortClientPrivate()
{
    Disconnect();
    // disconnect and kill socket
    if(IsActive())
            Cancel();
}


void QBtSerialPortClientPrivate::DoCancel()
{

}


// ----------------------------------------------------------------------------
// QBtSerialPortClientPrivate::ConnectL(THostName aName, TBTDevAddr aAddr, TInt aPort)
//
// create a connection to given address on given port.
// ----------------------------------------------------------------------------
TBool QBtSerialPortClientPrivate::Connect(
        const QBtDevice& remoteDevice,
        const QBtService& remoteService)
{
    if(iState != ENone)
        return false;

    device = new QBtDevice(remoteDevice);
    service = new QBtService(remoteService);

    // load protocol, RFCOMM
    TProtocolDesc pdesc;
    User::LeaveIfError(iSocketServ.FindProtocol(_L("RFCOMM"), pdesc));

    // open socket
    User::LeaveIfError(iSock.Open(iSocketServ, _L("RFCOMM")));
    // set address and port
    TBTSockAddr addr;
    addr.SetBTAddr(device->getAddress().convertToSymbianBtDevAddr());
    addr.SetPort(service->getPort());

    // connect socket
    TRequestStatus status;
    iSock.Connect(addr, status);
    User::WaitForRequest(status);
    if ( status!=KErrNone )
    {
        emit p_ptr->error(QBtSerialPortClient::BluetoothSPCErrorOpeningConnection);
        return false;
    }

    iState=EConnecting;
    ReceiveData();
    return true;
}


// ----------------------------------------------------------------------------
// QBtSerialPortClientPrivate::Disconnect()
//
// disconnect from remote device, shutdown connected socket
// ----------------------------------------------------------------------------
void QBtSerialPortClientPrivate::Disconnect()
{
    TRequestStatus status;
    // shutdown socket
    if (iState == ENone)
    {
        return;
    }

    iSock.CancelAll();
    iSock.Shutdown(RSocket::ENormal, status);
    User::WaitForRequest(status);
    iSock.Close();

    SafeDelete(device);
    SafeDelete(service);

    iState = ENone;
}

TBool QBtSerialPortClientPrivate::IsConnected()
{
    return (iState == ESending || iState == EWaiting);
}


// ----------------------------------------------------------------------------
// QBtSerialPortClientPrivate::SendData(const QString& data)
//
// send given data to remote device, write to connected socket
// ----------------------------------------------------------------------------
void QBtSerialPortClientPrivate::SendData(const QString& data)
{
    QByteArray tmpArray = data.toUtf8();
    TPtrC8 message8;
    message8.Set((const TUint8 *)tmpArray.constData(), tmpArray.size());

    // cancel any read requests on socket
    iSock.CancelRead();
    if(IsActive())
        Cancel();
    // send message
    iState=ESending;
    iSock.Write(message8, iStatus);
    SetActive();
}


// ----------------------------------------------------------------------------
// QBtSerialPortClientPrivate::ReceiveDataL()
//
// wait for and receive data from remote device, read connected socket
// ----------------------------------------------------------------------------
void QBtSerialPortClientPrivate::ReceiveData()
{
    // cancel pending operations
    iSock.CancelRead();
    if(IsActive())
        Cancel();
    // receive data from socket
    iState=EWaiting;
    iSock.RecvOneOrMore(iBuffer, 0, iStatus, iLen);
    SetActive();
}


void QBtSerialPortClientPrivate::RunL()
{
    if ( iStatus!=KErrNone )
    {
        HandleConnectorDisconnected();
        return;
    }

    switch (iState)
    {
        case EConnecting:
        {
            HandleConnectorConnected();
            // wait incoming data on socket
            ReceiveData();
            break;
        }
        case EWaiting:
        {
            // we got incoming data!
            /*HBufC8* text = HBufC8::NewLC(iBuffer.Length());
            text->Des()..Copy(iBuffer);*/
            // observer will handle data
            QString receivedString = QString::fromUtf8((char*)iBuffer.Ptr(), iBuffer.Size());
            HandleConnectorDataReceived(receivedString);
            //CleanupStack::PopAndDestroy(text);

            // start expecting new incoming data
            ReceiveData();
            break;
        }
        case ESending:
        {
            HandleConnectorDataSent();
            // start expecting new incoming data
            ReceiveData();
            break;
        }
        default:
            break;
    }
}

TInt QBtSerialPortClientPrivate::RunError(TInt /*aError*/)
{
    // Add error handling here, not implemented in this example
    return KErrNone;
}

// ----------------------------------------------------------------------------
// QBtSerialPortClientPrivate::HandleConnectorDataReceived(TDesC& aData)
//
// connector has received data signal
// ----------------------------------------------------------------------------
void QBtSerialPortClientPrivate::HandleConnectorDataReceived(const QString aData)
{
    emit p_ptr->dataReceived(aData);
}

/*!
 * HandleListenerConnected()
 *
 * Handles the event of server connection
 */
void QBtSerialPortClientPrivate::HandleConnectorConnected()
{
    emit p_ptr->connectedToServer();
}

/*!
 * HandleListenerDisconnected()
 *
 * Handles the event of server disconnection
 */
void QBtSerialPortClientPrivate::HandleConnectorDisconnected()
{
    emit p_ptr->disconnectedFromServer();
}

/*!
 * HandleConnectorDataSent()
 *
 * Data successfully sent to server
 */
void QBtSerialPortClientPrivate::HandleConnectorDataSent()
{
    emit p_ptr->dataSent();
}

