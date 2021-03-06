#-------------------------------------------------
#
# Project created by QtCreator 2018-05-17T16:27:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess_compete_platform
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    uiinput.cpp \
    uioutput.cpp \
    gamecontroller.cpp \
    humanagent.cpp \
    reversilogic.cpp \
    gomokulogic.cpp \
    clickablebutton.cpp \
    board.cpp

HEADERS  += mainwindow.h \
    logic.h \
    error_handling.h \
    board.h \
    agent.h \
    uiinput.h \
    uioutput.h \
    gamecontroller.h \
    player_color.h \
    InputPointObserver.h \
    humanagent.h \
    NaiveErrorHandling.h \
    reversilogic.h \
    gomokulogic.h \
    clickablebutton.h

FORMS    += mainwindow.ui
