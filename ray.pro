#-------------------------------------------------
#
# Project created by QtCreator 2015-04-12T17:15:56
#
#-------------------------------------------------

QT       += core
QT       += gui

TARGET = ray
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cc \
    glwindow.cc \
    raywindow.cc


QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    glwindow.hh \
    raywindow.hh

OTHER_FILES += \
    glsl.vert \
    glsl.frag

RESOURCES += \
    resource.qrc
