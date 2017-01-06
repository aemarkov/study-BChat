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
        webcam/videoviewer.cpp \
        webcam/frameconverter.cpp \
        crypto/cryptoapi.cpp

HEADERS  += mainwindow.h \
            webcam/cameraframegrabber.h \
            webcam/videoviewer.h \
            webcam/frameconverter.h \
            crypto/cryptoapi.h \
            CryptoPro/include/cpdrvlib.h \
            CryptoPro/include/cspmm.h \
            CryptoPro/include/cspvtable.h \
            CryptoPro/include/lfmm.h \
            CryptoPro/include/WinCryptEx.h \
            CryptoPro/include/wincsp.h \
            CryptoPro/include/wincspc.h \


FORMS    += mainwindow.ui

CONFIG += c++11
