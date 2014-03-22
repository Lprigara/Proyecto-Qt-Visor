#-------------------------------------------------
#
# Project created by QtCreator 2014-02-11T18:05:21
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia multimediawidgets
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = viewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    preferencias.cpp \
    capturebuffer.cpp \
    acerca.cpp

HEADERS  += mainwindow.h \
    preferencias.h \
    capturebuffer.h \
    acerca.h

FORMS    += mainwindow.ui \
    preferencias.ui \
    acerca.ui
