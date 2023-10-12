QT       += core gui\
           multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Anti.cpp \
    BloodBag.cpp \
    Bullet.cpp \
    Button.cpp \
    Devil.cpp \
    Enemy.cpp \
    Freezer.cpp \
    Hashtable.cpp \
    Health.cpp \
    Mask.cpp \
    Medal.cpp \
    Player.cpp \
    Ranking.cpp \
    Score.cpp \
    WildAnimal.cpp \
    boss.cpp \
    bossvirus.cpp \
    gameengine.cpp \
    gamerules.cpp \
    lose.cpp \
    main.cpp \
    mainwindow.cpp \
    props.cpp \
    virus.cpp \
    virusa.cpp \
    virusb.cpp \
    virusc.cpp \
    weapon.cpp \
    win.cpp

HEADERS += \
    Anti.h \
    BloodBag.h \
    Bullet.h \
    Button.h \
    Devil.h \
    Enemy.h \
    Freezer.h \
    Hashtable.h \
    Health.h \
    Mask.h \
    Medal.h \
    Player.h \
    Ranking.h \
    Score.h \
    WildAnimal.h \
    boss.h \
    bossvirus.h \
    constants.h \
    gameengine.h \
    gamerules.h \
    lose.h \
    mainwindow.h \
    props.h \
    virus.h \
    virusa.h \
    virusb.h \
    virusc.h \
    weapon.h \
    win.h

FORMS += \
    Ranking.ui \
    gameengine.ui \
    gamerules.ui \
    lose.ui \
    mainwindow.ui \
    win.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    reso.qrc

DISTFILES +=
