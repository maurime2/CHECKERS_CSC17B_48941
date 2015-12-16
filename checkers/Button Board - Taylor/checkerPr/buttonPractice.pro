#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T01:53:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = buttonPractice
TEMPLATE = app

QMAKE_MAC_SDK = macosx10.11


SOURCES += main.cpp\
        mainwindow.cpp \
    tile.cpp \
    board.cpp \
    menudialog.cpp \
    gameoverdialog.cpp

HEADERS  += mainwindow.h\
         tile.h\
         board.h \
    menudialog.h \
    gameoverdialog.h

FORMS    +=

RESOURCES += \
    images.qrc

DISTFILES +=
