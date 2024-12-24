QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/login.cpp \
    Model/rtpclient.cpp \
    ModelView/loginviewmodel.cpp \
    ModelView/mainviewmodel.cpp \
    ModelView/rtpclientviewmodel.cpp \
    ModelView/streamingviewmodel.cpp \
    ModelView/viewmodel.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    streamingwidget.cpp

HEADERS += \
    Model/login.h \
    Model/rtpclient.h \
    ModelView/loginviewmodel.h \
    ModelView/mainviewmodel.h \
    ModelView/rtpclientviewmodel.h \
    ModelView/streamingviewmodel.h \
    ModelView/viewmodel.h \
    logindialog.h \
    mainwindow.h \
    streamingwidget.h

FORMS += \
    logindialog.ui \
    mainwindow.ui \
    streamingwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
