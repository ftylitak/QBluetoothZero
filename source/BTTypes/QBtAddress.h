/*
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

#ifndef QBTADDRESS_H
#define QBTADDRESS_H

#include <QtCore/QString.h>
#include <QtCore/QByteArray.h>
#include <QBtGlobal.h>

#ifdef Q_OS_SYMBIAN
#include <bttypes.h>
#endif

QBT_NAMESPACE_BEGIN

/**
 * Class that represents the device's bluetooth _address.
 * It is one of the main fields of QBtDevice.
 */
class DLL_EXPORT QBtAddress : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString _address READ toString)// WRITE setName)

public:

    /**
     * QBtAddress()
     * Default constructor. 
     */
    QBtAddress();

    /**
     * QBtAddress()
     * Copy constructor
     */
    QBtAddress (const QBtAddress& other);

    QBtAddress (const QByteArray& byteArray);
    QBtAddress (const QString& addr);
    
#ifdef Q_OS_SYMBIAN
    QBtAddress (const TBTDevAddr& addr);
#endif
    /**
     * Mainly created because on windows bluesoleil sdk, bluetooth _address
     * byte array is reversed so it is usefull to provide this functionality
     * here
     *
     * @param reversedArray
     */
    static QBtAddress& getAddressFromReversedArray (const QByteArray & reversedArray);

    ~QBtAddress ();

    /**
     * @return true if the _address contained in this instance is
     * a valid bluetooth _address
     */
    bool isValid () const;

    /**
     * Returns a string representation of this bluetooth _address
     */
    QString toString() const;

    /**     
     * Returns a 6-byte array representation of the bluetooth _address
     */
    QByteArray toByteArray() const; // Symbian representation

    /**
     * Returns a 6-byte array representation of the bluetooth _address
     * in reversed order. Mainly created for convenience when using
     * windows bluesoleil SDK.
     */
    QByteArray toReversedByteArray() const; // windows representation

    QBtAddress& operator= (const QBtAddress & other );
    bool operator!= (const QBtAddress & other );
    bool operator== (const QBtAddress & other );
    bool operator< (const QBtAddress & other );

#ifdef Q_OS_SYMBIAN
    TBTDevAddr convertToSymbianBtDevAddr() const;
#endif

private:
    QString _address;
    bool _valid;
};

QBT_NAMESPACE_END

Q_DECLARE_METATYPE(QBT_NAMESPACE_NAME::QBtAddress)

#endif // QBTADDRESS_H
