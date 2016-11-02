TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    account.cpp \
    game.cpp \
    hero.cpp \
    alchemist.cpp \
    lifestealer.cpp \
    facelessvoid.cpp \
    juggernaut.cpp

HEADERS += \
    encrypt.h \
    account.h \
    game.h \
    hero.h \
    alchemist.h \
    lifestealer.h \
    facelessvoid.h \
    juggernaut.h
