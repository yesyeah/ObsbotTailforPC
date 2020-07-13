QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = title_logo.ico
CONFIG += c++11
LIBS += C:\Users\Kevin\Desktop\obsbotDestopAPP\desktopApp\curl-7.70.0-win64-mingw\lib\libcurl.dll.a
LIBS += C:\Users\Kevin\Desktop\obsbotDestopAPP\desktopApp\openssl-1.1.1g-win64-mingw\lib\libcrypto.dll.a
LIBS += C:\Users\Kevin\Desktop\obsbotDestopAPP\desktopApp\openssl-1.1.1g-win64-mingw\lib\libssl.dll.a
LIBS += -lIphlpapi -lSensapi -lws2_32

INCLUDEPATH +=  C:\Users\Kevin\Desktop\obsbotDestopAPP\desktopApp\curl-7.70.0-win64-mingw\include\
INCLUDEPATH += C:\Users\Kevin\Desktop\obsbotDestopAPP\desktopApp\json\include\

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    devicelistwindow.cpp \
    httpservice.cpp \
    icmp_ping.cpp \
    cameracontrol.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    remoservice.cpp \
    switchbutton.cpp \
    utils.cpp

HEADERS += \
    devicelistwindow.h \
    httpservice.h \
    icmp_ping.h \
    cameracontrol.h \
    loginwindow.h \
    mainwindow.h \
    remoprotocolutils.h \
    remoservice.h \
    switchbutton.h \
    utils.h

FORMS += \
    devicelistwindow.ui \
    loginwindow.ui \
    mainwindow.ui

TRANSLATIONS += \
    desktopApp_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \

RESOURCES += \
    resource.qrc
