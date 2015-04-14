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
    literals.h \
    compiler_generated_functions.h \
<<<<<<< HEAD
    smart_pointers.h
=======
    deducing_types.h
>>>>>>> 3e1f27ac4a5b4b85f9f5391a4208ca4a49b81235

QMAKE_CXXFLAGS += -std=gnu++0x
