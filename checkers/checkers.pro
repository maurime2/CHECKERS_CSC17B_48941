#-------------------------------------------------
#
# Project created by QtCreator 2015-10-27T11:04:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = checkers
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    menudialog.cpp \
    board.cpp \
    boardsquare.cpp

HEADERS  += mainwindow.h \
    menudialog.h \
    board.h \
    boardsquare.h \
    piece.h

RESOURCES += \
    checkers.qrc
