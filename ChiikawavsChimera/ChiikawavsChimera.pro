QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    enemybase.cpp \
    enemybig.cpp \
    enemyboss.cpp \
    enemybubble.cpp \
    enemybullet.cpp \
    enemychimera.cpp \
    enemyinsect.cpp \
    expball.cpp \
    gamecontrol.cpp \
    gamedefine.cpp \
    gameobject.cpp \
    main.cpp \
    gamewidget.cpp \
    mybutton.cpp \
    mydialog.cpp \
    mygraphicsview.cpp \
    myselectivebutton.cpp \
    player.cpp \
    playerbullet.cpp

HEADERS += \
    bullet.h \
    enemybase.h \
    enemybig.h \
    enemyboss.h \
    enemybubble.h \
    enemybullet.h \
    enemychimera.h \
    enemyinsect.h \
    expball.h \
    gamecontrol.h \
    gamedefine.h \
    gameobject.h \
    gamewidget.h \
    mybutton.h \
    mydialog.h \
    mygraphicsview.h \
    myselectivebutton.h \
    player.h \
    playerbullet.h

FORMS += \
    gamewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imgs.qrc \
    sounds.qrc
