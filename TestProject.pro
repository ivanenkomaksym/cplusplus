#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T18:16:30
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = TestProject
CONFIG   += console
CONFIG   += C++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

HEADERS += \
    move_semantics.h \
    deducing_types.h

QMAKE_CXXFLAGS += -std=gnu++0x