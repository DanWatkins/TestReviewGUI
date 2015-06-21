TEMPLATE = app

QT += qml quick widgets

CONFIG += c++14

SOURCES += main.cpp \
    TestResultsTableModel.cpp \
    TestResult.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    TestResultsTableModel.h \
    TestResult.h
