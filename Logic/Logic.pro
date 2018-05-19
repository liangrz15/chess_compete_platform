QT += core
QT -= gui

TARGET = Logic
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gomokulogic.cpp \
    logic.cpp \
    board.cpp \
    reversilogic.cpp

HEADERS += \
    board.h \
    gomokulogic.h \
    logic.h \
    player_color.h \
    reversilogic.h

