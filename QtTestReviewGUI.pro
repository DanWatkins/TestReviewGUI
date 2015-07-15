TEMPLATE = app
VERSION = 1.0.0.1

QT += qml quick widgets

CONFIG += c++14

SOURCES += main.cpp \
    TestResultsTableModel.cpp \
    TestResult.cpp \
    Appstate.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    TestResultsTableModel.h \
    TestResult.h \
    Appstate.h
