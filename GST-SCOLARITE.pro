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
    professor.cpp \
    signup.cpp \
    subject.cpp

HEADERS += \
    auth.h \
    db_connection.h \
    forgotpassword.h \
    mainwindow.h \
    professor.h \
    signup.h \
    subject.h

FORMS += \
    auth.ui \
    branches.ui \
    classrooms.ui \
    departments.ui \
    episodes.ui \
    forgotpassword.ui \
    mainwindow.ui \
    plannings.ui \
    professor.ui \
    signup.ui \
    subject.ui

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

DISTFILES += \
    ../../../Downloads/logout.png
