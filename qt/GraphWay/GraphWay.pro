TEMPLATE = app

QT += core gui widgets sql

TARGET = GraphWay

CONFIG  += axcontainer

SOURCES += main.cpp \
    data_types/endpoint.cpp \
    data_types/way.cpp \
    data_types/graph.cpp \
    hight_level/wayfinder.cpp \
    hight_level/graphbuilder.cpp \
    low_level/dataimporter.cpp \
    low_level/umlbuilder.cpp \
    logger.cpp \
    mainwindow.cpp \
    wayendpointschoosedialog.cpp

HEADERS += \
    data_types/endpoint.h \
    data_types/way.h \
    data_types/graph.h \
    hight_level/wayfinder.h \
    hight_level/graphbuilder.h \
    low_level/dataimporter.h \
    low_level/umlbuilder.h \
    logger.h \
    mainwindow.h \
    wayendpointschoosedialog.h

FORMS += \
    mainwindow.ui \
    wayendpointschoosedialog.ui
