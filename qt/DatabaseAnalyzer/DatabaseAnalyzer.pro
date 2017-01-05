TEMPLATE = app

QT += gui widgets
LIBS += -lsqlite3

SOURCES += main.cpp \
    hight_level/databasereporter.cpp \
    hight_level/databaseanalyzer.cpp \
    low_level/databasewrapper.cpp \
    data_types/table.cpp \
    data_types/tablerow.cpp \
    data_types/string.cpp \
    data_types/number.cpp \
    logger.cpp \
    low_level/sql_query.cc \
    mainwindow.cpp \
    filterdialog.cpp

RESOURCES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    hight_level/databasereporter.h \
    hight_level/databaseanalyzer.h \
    low_level/databasewrapper.h \
    data_types/table.h \
    data_types/tablerow.h \
    data_types/primitivetype.h \
    data_types/string.h \
    data_types/number.h \
    logger.h \
    low_level/sql_query.h \
    mainwindow.h \
    filterdialog.h

FORMS += mainwindow.ui \
    filterdialog.ui
