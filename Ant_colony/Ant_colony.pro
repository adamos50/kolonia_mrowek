#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T21:30:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ant_colony
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    ant.cpp

HEADERS  += dialog.h \
    ant.h \
    constants.h

FORMS    += dialog.ui
