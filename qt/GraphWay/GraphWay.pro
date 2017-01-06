QT += core gui

TARGET = GraphWay
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    data_types/endpoint.cpp \
    data_types/line.cpp \
    hight_level/wayfinder.cpp \
    data_types/graph.cpp

HEADERS += \
    data_types/endpoint.h \
    data_types/line.h \
    hight_level/wayfinder.h \
    data_types/graph.h
