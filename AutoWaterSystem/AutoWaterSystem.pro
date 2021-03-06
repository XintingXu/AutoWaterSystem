#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T20:30:30
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoWaterSystem
TEMPLATE = app

PRECOMPILED_HEADER = stable.h
QMAKE_CXX = ccache g++

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    PictureOperarion.cpp \
    NetworkOperation.cpp \
    DeviceControl.cpp \
    getSensorInformation.cpp \
    uploadSensorInformation.cpp

HEADERS  += mainwindow.h \
    NetworkOperation.h \
    PictureOperation.h \
    DeviceControl.h \
    getSensorInformation.h \
    uploadSensorInformation.h

FORMS    += mainwindow.ui

LIBS += /usr/lib/arm-linux-gnueabihf/libopencv_highgui.so \
        /usr/lib/arm-linux-gnueabihf/libopencv_core.so    \
        /usr/lib/arm-linux-gnueabihf/libopencv_imgproc.so\
        -lwiringPi
