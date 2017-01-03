TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    databasereporter.cpp \
    databaseanalyzer.cpp \
    databasewrapper.cpp \
    table.cpp \
    tablerow.cpp \
    primitivetype.cpp \
    string.cpp \
    number.cpp \
    logger.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    databasereporter.h \
    databaseanalyzer.h \
    databasewrapper.h \
    table.h \
    tablerow.h \
    primitivetype.h \
    string.h \
    number.h \
    logger.h
