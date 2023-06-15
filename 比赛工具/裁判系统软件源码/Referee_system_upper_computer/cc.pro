#-------------------------------------------------
#
# Project created by QtCreator 2023-04-30T17:16:57
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
RC_ICONS = sys.ico
RC_FILE += logo.rc
QT      +=multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cc
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        qwight.cpp

HEADERS += \
        qwight.h

FORMS += \
        qwight.ui

RESOURCES += \
    ioc.qrc

DISTFILES += \
    logo.rc \
    Summoning_Glory.mp3
