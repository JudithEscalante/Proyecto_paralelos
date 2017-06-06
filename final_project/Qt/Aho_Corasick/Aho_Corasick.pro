#-------------------------------------------------
#
# Project created by QtCreator 2016-07-30T23:37:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Aho_Corasick
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    automata.h \
    automata_noD.h

FORMS    += mainwindow.ui

RESOURCES += \
    image.qrc
