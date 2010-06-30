/*
 * QBtSerialPortServer_stub.h
 *
 *
 *      Author: Ftylitakis Nikolaos
 */

#ifndef QBTSERIALPORTSERVER_STUB_H_
#define QBTSERIALPORTSERVER_STUB_H_

#include "QBtSerialPortServer.h"

class QBtSerialPortServerPrivate
{
public:
    QBtSerialPortServerPrivate(QBtSerialPortServer* punlicClsass);
    ~QBtSerialPortServerPrivate();

    void StartListener();
    void StopListener();
    void SendData(const QString data);

private:
    QBtSerialPortServer* p_ptr;
};

#endif /* QBTSERIALPORTSERVER_STUB_H_ */
