#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T18:16:30
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = TestProject
CONFIG   += console
CONFIG   += C++14
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

HEADERS += \
    move_semantics.h \
    literals.h \
    compiler_generated_functions.h \
    smart_pointers.h \
    smart_pointers.h \
    deducing_types.h \
    cplusplus11features.h \
    resource_managing_class.h \
    constness.h

QMAKE_CXXFLAGS += -std=c++11
