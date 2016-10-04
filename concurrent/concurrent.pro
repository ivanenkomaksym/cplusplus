QT += core
QT -= gui

TARGET = concurrent
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++11
