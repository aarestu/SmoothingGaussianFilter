#-------------------------------------------------
#
# Project created by QtCreator 2014-02-24T14:06:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = GaussianFilter
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp


INCLUDEPATH += D://opencv//sources//opencv_bin//install//include

LIBS += D://opencv//sources//opencv_bin//bin//*.dll
