QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth.cpp \
    db_connection.cpp \
    forgotpassword.cpp \
    main.cpp \
    mainwindow.cpp \
    signup.cpp

HEADERS += \
    auth.h \
    db_connection.h \
    forgotpassword.h \
    mainwindow.h \
    signup.h

FORMS += \
    auth.ui \
    forgotpassword.ui \
    mainwindow.ui \
    signup.ui

TRANSLATIONS += \
    GST-SCOLARITE_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
