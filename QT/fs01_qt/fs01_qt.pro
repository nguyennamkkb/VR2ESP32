#-------------------------------------------------
#
# Project created by QtCreator 2021-09-06T14:01:23
#
#-------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fs01_qt
TEMPLATE = app


SOURCES += main.cpp\
        fs01_qt.cpp \
    n_serial.cpp \
    fs_01.cpp \
    udp_thread.cpp \
    ima.cpp

HEADERS  += fs01_qt.h \
    n_serial.h \
    fs_01.h \
    udp_thread.h \
    wav.h \
    ima.h

FORMS    += fs01_qt.ui
