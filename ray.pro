#-------------------------------------------------
#
# Project created by QtCreator 2015-04-12T17:15:56
#
#-------------------------------------------------

QT       += core
QT       += gui

TARGET    = ray
CONFIG   += app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cc \
    glwindow.cc \
    raywindow.cc

HEADERS += \
    glwindow.hh \
    raywindow.hh

RESOURCES += \
    resource.qrc
