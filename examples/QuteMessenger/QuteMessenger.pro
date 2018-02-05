TEMPLATE = app
TARGET = QuteMessenger
QT += core \
    gui
HEADERS += QChatWidgetClient.h \
    QChatWidgetServer.h \
    QChatWidget.h \
    QuteMessenger.h \
    QInputBox.h
SOURCES += QChatWidgetClient.cpp \
    QChatWidgetServer.cpp \
    QChatWidget.cpp \
    main.cpp \
    QuteMessenger.cpp \
    QInputBox.cpp
FORMS += chatWidget.ui \
    QuteMessenger.ui
RESOURCES += imageResources.qrc
symbian {
    INCLUDEPATH += /epoc32/include/QBluetoothZero
    TARGET.UID3 = 0xE8D3B2DA
    LIBS += -lQBluetoothZero

    TARGET.CAPABILITY = LocalServices \
        NetworkServices \
        ReadUserData \
        UserEnvironment \
        WriteUserData
    
  customrules.pkg_prerules  = \
        ";QBluetoothZero" \
        "@\"$$(EPOCROOT)Epoc32/InstallToDevice/QBluetoothZero_selfsigned.sis\",(0xA003328D)"\
        " "
	
        DEPLOYMENT += customrules
}
win32 {
    LIBS +=  -lQBluetoothZero

    INCLUDEPATH += ./QBluetoothZero
    HEADERS += QBluetoothZero.h
}
ICON = val1.svg
