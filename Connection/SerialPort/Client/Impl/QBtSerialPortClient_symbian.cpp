/*
 * QBtSerialPortClient_symbian.cpp
 *
 *
 *      Author: Ftylitakis Nikolaos, Luis Valente
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
    if (iSocketServ.Connect() != KErrNone)
       QT_TRYCATCH_LEAVING (emit p_ptr->error(QBtSerialPortClient::ErrorUnavailable) );
    
    
    // timer
    iTimer = CPeriodic::NewL (CIdle::EPriorityIdle);
    
}


QBtSerialPortClientPrivate::QBtSerialPortClientPrivate(QBtSerialPortClient* publicClass)
 : CActive(CActive::EPriorityStandard),
   iState(ENone),
   p_ptr(publicClass)
{
    CActiveScheduler::Add(this);
}


QBtSerialPortClientPrivate::~QBtSerialPortClientPrivate()
{
    Disconnect();
    
    // delete connect timer
    CancelConnectionTimer();
    delete iTimer;
    
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
TBool QBtSerialPortClientPrivate::ConnectL (const QBtDevice& remoteDevice, const QBtService& remoteService)
{		
	//DEBUG_MSG ("[connect] entering");
	
    if (iState != ENone)        
    { DEBUG_MSG("warning: trying to connect and state != ENone"); return false; }

    device =  remoteDevice;
    service = remoteService;

    // load protocol, RFCOMM
    TProtocolDesc pdesc;
    User::LeaveIfError(iSocketServ.FindProtocol(_L("RFCOMM"), pdesc));

    // open socket
    User::LeaveIfError(iSock.Open(iSocketServ, _L("RFCOMM")));
    
    // set address and port
    TBTSockAddr addr;
    addr.SetBTAddr(device.getAddress().convertToSymbianBtDevAddr());
    addr.SetPort(service.getPort());

    // connect socket
    TRequestStatus status;
    iSock.Connect(addr, status);  
    
    
    iState = EConnecting;
    
    // start connection timer    
    DEBUG_MSG ("[connect] start timer");
    StartConnectionTimer();
    
            
    // wait (should we wait here? or use the ActiveObject RunL ?)
    DEBUG_MSG ("[connect] waiting for request");
    User::WaitForRequest(status);
    
    
    // cancel timers    
    DEBUG_MSG ("[connect] ok, canceling timer");
    CancelConnectionTimer();
    
    
    if (status != KErrNone)
    {
    	DEBUG_MSG (QString ("error detected: %1").arg (status.Int()) );
    	
    	iState = ENone;
    	
    	switch (status.Int())
    	{
    		case KErrTimedOut:
    		case KErrCancel:
    			QT_TRYCATCH_LEAVING (emit p_ptr->error(QBtSerialPortClient::ErrorConnectionTimeout) );
    			break;
    			
    		case KErrAlreadyExists:
				QT_TRYCATCH_LEAVING (emit p_ptr->error(QBtSerialPortClient::ErrorAlreadyConnected) );
				break;
    			
    		case KErrCouldNotConnect:
    		default:
    			QT_TRYCATCH_LEAVING (emit p_ptr->error(QBtSerialPortClient::ErrorOpeningConnection) );
    	
    	}
    	
        return false;
    }

       
    // prepare for receive
    DEBUG_MSG ("[connect] prepare for receive");
    ReceiveData();
   
    // notify
    DEBUG_MSG ("[connect] emit signal");
    QT_TRYCATCH_LEAVING (emit p_ptr->connectedToServer() );
    
        
    //SetActive();   
    DEBUG_MSG ("[connect] return");
    return true;
    
}


// ----------------------------------------------------------------------------
// callback for notifying connection timeout 
//
// ----------------------------------------------------------------------------

TInt QBtSerialPortClientPrivate::ConnectTimerCallBack (TAny* aPtr)
{
	DEBUG_MSG ("[timer] entering");
	
	QBtSerialPortClientPrivate* p = (QBtSerialPortClientPrivate*) aPtr;
		
	// ignore if connection was successful
	if (p->iState != EConnecting)
	{
		DEBUG_MSG ("[timer] got connection, ignoring timeout event");
		return EFalse;
	}	
	
	DEBUG_MSG ("[timer] canceling ActiveObject");
	
	
	if (p->IsActive())
		p->Cancel();
	
	// change state
	p->iState = ENone;
	
	DEBUG_MSG ("[timer] emit error signal");
	
	// emit error
	QT_TRYCATCH_LEAVING (emit p->p_ptr->error (QBtSerialPortClient::ErrorConnectionTimeout));
	
	DEBUG_MSG ("[timer] end");
	
	return EFalse;	
}


void QBtSerialPortClientPrivate::StartConnectionTimer()
{	
	// 30s interval (this should be a parameter)
	TTimeIntervalMicroSeconds32 interval (30 * 1000*1000);	
	
	if (iTimer)
		iTimer->Start (interval, interval, TCallBack (ConnectTimerCallBack, this) );	
}

void QBtSerialPortClientPrivate::CancelConnectionTimer()
{
	if (iTimer)
		iTimer->Cancel();
}

// ----------------------------------------------------------------------------
// QBtSerialPortClientPrivate::Disconnect()
//
// disconnect from remote device, shutdown connected socket
// ----------------------------------------------------------------------------
void QBtSerialPortClientPrivate::Disconnect()
{    
    DEBUG_MSG ("disconnected called")
	
	if (iState == ENone || iState == EDisconnecting)
    	return;
    
    // 
    iState = EDisconnecting;
    
    
    // cancel timers
    CancelConnectionTimer();
    
    
    // shutdown socket
    TRequestStatus status;
    
    
    // cancel all
    iSock.CancelAll();
    iSock.Shutdown(RSocket::ENormal, status);
    User::WaitForRequest(status);
    iSock.Close();

    iState = ENone;
    
    // check 
    if (status == KErrNone)
    {    	
    	QT_TRYCATCH_LEAVING (emit p_ptr->disconnectedFromServer() );	
    }
    else
    {
    	QT_TRYCATCH_LEAVING (emit p_ptr->error(QBtSerialPortClient::ErrorOnDisconnecting) );
    }        
    
        
    //iState = EDisconnecting;    
    // SetActive();
    // notification will be in RunL with KErrCancel (in case of using SetActive)
    
}

TBool QBtSerialPortClientPrivate::IsConnected()
{
    return (iState == ESending || iState == EWaiting);
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
    
    if (IsActive())
    	Cancel();
    
    // send message
    iState = ESending;
    
    iSock.Write(message8, iStatus);
    SetActive();
    
}


// ----------------------------------------------------------------------------
// 
// ----------------------------------------------------------------------------
void QBtSerialPortClientPrivate::RunL()
{
	DEBUG_MSG (QString ("[RunL status: %1 state: %2]").arg (iStatus.Int()).arg (iState) );
	
	// cancel possible timers
	CancelConnectionTimer();
	
	
	// see what's happened
    if (iStatus != KErrNone)
    {
    	switch (iStatus.Int() )
    	{    		    		
    		// we were disconnected (by us)    		
    		case KErrCancel:
    		{    			
    			iState = ENone;    			
    			// ignore this signal for now as Disconnect() is using WaitForRequest
    			// QT_TRYCATCH_LEAVING (emit p_ptr->disconnectedFromServer() );
    			
    			return;
    		}
    		
    			
    		// we were disconnected by peer	
    		case KErrDisconnected:
    		{
    			iState = ENone;
    			QT_TRYCATCH_LEAVING (emit p_ptr->connectionResetByPeer() );
    			return;
    		}
    			
    			
    		// not ready to initiate new operation (something is still underway)
    		case KErrNotReady:
    		{	
    			// no change in current state (?)    			
    			QT_TRYCATCH_LEAVING (emit p_ptr->error (QBtSerialPortClient::ErrorAlreadyInUse) );
    			return;
    		}
    		
    	}
    	
    	
    	
    	DEBUG_MSG (QString ("[RunL error: %1]").arg (iStatus.Int()));    	
    	    	
    	// get the error
    	switch (iState)
    	{
    		case EConnecting:
    		{
    			QT_TRYCATCH_LEAVING (emit p_ptr->error (QBtSerialPortClient::ErrorOpeningConnection) );
    			break;
    		}	
    		
    		case EWaiting:
    		case ESending:
    		{
    			QT_TRYCATCH_LEAVING (emit p_ptr->error (QBtSerialPortClient::ErrorConnectionError));
    			break;
    		}
    		
    		default:
    			QT_TRYCATCH_LEAVING (emit p_ptr->error (QBtSerialPortClient::ErrorUndefinedError));
    			break;
    			
    			
    	}   	
    	
    	iState = ENone; 
        return;
    }

    
    
    // no error
    switch (iState)
    {
    	// notification should be the last thing because the user might change the state of the
    	// object, for example, by calling SendData() in a slot for the 'connectedToServer' signal
    	
        case EConnecting:
        {	
        	// this one would run only if SetActive() is called in connect()        	
        	iState = EIdle;
        	
        	// wait incoming data on socket
            ReceiveData();
        	
        	// notify
        	QT_TRYCATCH_LEAVING (emit p_ptr->connectedToServer() );     	
            break;
        }
        
        case EWaiting:
        {                	
        	// we got incoming data!            
            QString receivedString = QString::fromUtf8((char*)iBuffer.Ptr(), iBuffer.Size());
            
            // start expecting new incoming data
            ReceiveData();
            
            // notify
            QT_TRYCATCH_LEAVING (emit p_ptr->dataReceived (receivedString) );            
            break;
        }
        case ESending:
        {                	
            // start expecting new incoming data
            ReceiveData();
            
            // notify
            QT_TRYCATCH_LEAVING  (emit p_ptr->dataSent() );
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
// QBtSerialPortClientPrivate::HandleConnectorDataReceivedL(TDesC& aData)
//
// connector has received data signal
// ----------------------------------------------------------------------------
void QBtSerialPortClientPrivate::HandleConnectorDataReceivedL(const QString & aData)
{
	
}

/*!
 * HandleListenerConnected()
 *
 * Handles the event of server connection
 */
void QBtSerialPortClientPrivate::HandleConnectorConnectedL()
{
	
}

/*!
 * HandleListenerDisconnected()
 *
 * Handles the event of server disconnection
 */
void QBtSerialPortClientPrivate::HandleConnectorDisconnectedL()
{
	
}

/*!
 * HandleConnectorDataSentL()
 *
 * Data successfully sent to server
 */
void QBtSerialPortClientPrivate::HandleConnectorDataSentL()
{
	
}

