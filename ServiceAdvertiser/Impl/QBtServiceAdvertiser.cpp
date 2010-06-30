/*
 * QBtServiceAdvertiser.cpp
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#include "../QBtServiceAdvertiser.h"
#include <QBtAuxFunctions.h>

#if defined(Q_OS_SYMBIAN)
#include "../QBtServiceAdvertiser_symbian.h"
#elif defined(Q_OS_WIN32)
#include "../QBtServiceAdvertiser_win32.h"
#elif !defined(Q_OS_WIN32) && !defined(Q_OS_SYMBIAN)
#include "../QBtServiceAdvertiser_stub.h"
#endif

//////////////////////////////////////////////////
// QBtServiceAdvertiser::QBtServiceAdvertiser()	//
// Defaul constructor							//
//////////////////////////////////////////////////
QBtServiceAdvertiser::QBtServiceAdvertiser(QObject *parent) :
    QObject(parent), _localService(NULL)
{
#ifdef Q_OS_SYMBIAN
    QT_TRAP_THROWING(_implPtr = QBtServiceAdvertiserPrivate::NewL(this));
#else
    _implPtr = new QBtServiceAdvertiserPrivate(this);
#endif
}

QBtServiceAdvertiser::~QBtServiceAdvertiser()
{
    stopAdvertising();

    SafeDelete(_localService);
    SafeDelete(_implPtr);
}

/**
 * startAdvertising(const QBtService& service)
 */
void QBtServiceAdvertiser::startAdvertising(const QBtService& service)
{
    _localService = new QBtService(service);
    _implPtr->StartAdvertiser(service);
}

/**
 * stopAdvertising()
 */
void QBtServiceAdvertiser::stopAdvertising()
{
    _implPtr->StopAdvertiser();
}

/**
 *
 */
void QBtServiceAdvertiser::updateAvailability(bool aAvailable)
{
    _implPtr->UpdateAvailability(aAvailable);
}
