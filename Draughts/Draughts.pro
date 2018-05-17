#-------------------------------------------------
#
# Project created by QtCreator 2017-09-05T13:26:27
#
#-------------------------------------------------

QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Draughts
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    draughts.cpp \
    mydraughts.cpp

HEADERS  += dialog.h \
    draughts.h \
    mydraughts.h

FORMS    += dialog.ui \
    draughts.ui \
    mydraughts.ui
