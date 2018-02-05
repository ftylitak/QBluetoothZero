QT       += core gui declarative

TARGET = RemoteBrowser
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += remotebrowser.h

SOURCES += main.cpp \
            remotebrowser.cpp

win32 {
    LIBS +=  -lQBluetooth/bin/Release/QBluetooth \
                -lBlueSoleil_SDK_2.0.5/bin/BsSDK

    INCLUDEPATH += QBluetooth/include
    HEADERS += QBluetooth/include/QBluetooth.h
}



