#-------------------------------------------------
#
# Project created by QtCreator 2015-09-11T16:18:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = lab1_ui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    classes/bankrecord.cpp \
    classes/binarytree.cpp \
    classes/bankrecord_ext.cpp

HEADERS  += mainwindow.h \
    classes/bankrecord.h \
    classes/binarytree.h \
    classes/bankrecord_ext.h

FORMS    += mainwindow.ui

RESOURCES +=
