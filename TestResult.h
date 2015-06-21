#ifndef TestResult_h
#define TestResult_h

#include <QtCore/QString>

struct TestResult
{
    enum class Status
    {
        None,
        Passed,
        Failed,
        Skipped,
        Blacklisted
    };

    enum class Role
    {
        Status = Qt::UserRole+1,
        ClassName,
        TestName,
        Message
    };

    Status status       = Status::None;
    QString className   = "";
    QString testName    = "";
    QString message     = "";
};

#endif
