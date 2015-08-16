//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#ifndef TestResult_h
#define TestResult_h

#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QDebug>

class TestResult : public QObject
{
    Q_OBJECT

public:
    TestResult(QObject *parent=nullptr) : QObject(parent) {}

public:
    enum Status
    {
        None,
        Passed,
        Failed,
        Skipped,
        Blacklisted
    }; Q_ENUMS(Status)


    enum class Role
    {
        Status = Qt::UserRole+1,
        ClassName,
        TestName,
        Message,
        FilePath,
        FileLineNumber
    };

    //TODO can we use vbase::Property here?
    Status status       = Status::None;
    QString className   = "";
    QString testName    = "";
    QString message     = "";

    QString filePath    = "";
    int fileLineNumber  = 0;

    QString statusAsString() const;
};

#endif
