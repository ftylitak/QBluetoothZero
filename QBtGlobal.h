#ifndef QBTGLOBAL_H
#define QBTGLOBAL_H

#include <qglobal.h>

#ifdef BLUETOOTH_LIB
#define DLL_EXPORT Q_DECL_EXPORT
#else
#define DLL_EXPORT Q_DECL_IMPORT
#endif

#endif // QBTGLOBAL_H
