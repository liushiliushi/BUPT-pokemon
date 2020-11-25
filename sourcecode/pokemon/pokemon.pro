QT       += core gui
QT  += multimedia
QT += sql
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    bagwidget.cpp \
    choose.cpp \
    choose2.cpp \
    fightwidget.cpp \
    listitem.cpp \
    lobby.cpp \
    login.cpp \
    main.cpp \
    manager.cpp \
    mypushbutton.cpp \
    pokemon.cpp \
    resultwidget.cpp \
    spiritinfo.cpp \
    userinfo.cpp \
    userlist.cpp \
    widget.cpp

HEADERS += \
    bagwidget.h \
    choose.h \
    choose2.h \
    config.h \
    fightwidget.h \
    listitem.h \
    lobby.h \
    login.h \
    manager.h \
    mypushbutton.h \
    pokemon.h \
    resultwidget.h \
    spiritinfo.h \
    userinfo.h \
    userlist.h \
    widget.h

FORMS += \
    bagwidget.ui \
    choose.ui \
    choose2.ui \
    fightwidget.ui \
    lobby.ui \
    login.ui \
    resultwidget.ui \
    spiritinfo.ui \
    userinfo.ui \
    userlist.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

