#ifndef QBTADDRESS_H
#define QBTADDRESS_H

#include <QString>
#include <QByteArray>
#include <QBtGlobal.h>

#ifdef Q_OS_SYMBIAN
#include <bttypes.h>
#endif

/**
 * Class that represents the device's bluetooth _address.
 * It is one of the main fields of QBtDevice.
 */
class DLL_EXPORT QBtAddress
{
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
    // really needed?
    //QBtAddress (const QBtAddress& other);

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
    static QBtAddress getAddressFromReversedArray (const QByteArray & reversedArray);

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

    
    // really needed?
    //QBtAddress& operator= (const QBtAddress & other );
    
    bool operator!= (const QBtAddress & other );
    bool operator== (const QBtAddress & other );
    bool operator< (const QBtAddress & other );

#ifdef Q_OS_SYMBIAN
    TBTDevAddr convertToSymbianBtDevAddr();
#endif

private:
    QString _address;
    bool _valid;
};

#endif // QBTADDRESS_H
