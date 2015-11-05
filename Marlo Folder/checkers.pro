#-------------------------------------------------
#
# Project created by QtCreator 2015-10-08T11:27:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = checkers
TEMPLATE = app


SOURCES += main.cpp\
    board.cpp \
    boardsquare.cpp \
    mainwindow.cpp \
    menu.cpp \
    menudialog.cpp

HEADERS  += \
    board.h \
    boardsquare.h \
    mainwindow.h \
    menu.h \
    menudialog.h

RESOURCES += \
    checkers.qrc

