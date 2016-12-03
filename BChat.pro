#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27T16:25:30
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BChat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        webcam/cameraframegrabber.cpp \
    webcam/videoviewer.cpp

HEADERS  += mainwindow.h \
    webcam/cameraframegrabber.h \
    webcam/videoviewer.h

FORMS    += mainwindow.ui

CONFIG += c++11
