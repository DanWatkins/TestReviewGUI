#include "TestResultsTableModel.h"
#include <QDebug>
#include <QtCore/QFile>
#include <QtCore/QRegularExpression>

TestResultsTableModel::TestResultsTableModel()
{
    parseFile("");
}

int TestResultsTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mTestResults.size();
}


int TestResultsTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}


QVariant TestResultsTableModel::data(const QModelIndex &index, int role) const
{
    const TestResult &testResult = mTestResults[index.row()];

    switch (static_cast<TestResult::Role>(role))
    {
    case TestResult::Role::Status:
        return "TODO";
    case TestResult::Role::ClassName:
        return testResult.className;
    case TestResult::Role::TestName:
        return testResult.testName;
    case TestResult::Role::Message:
        return testResult.message;
    }

    return QVariant::Invalid;
}


QHash<int, QByteArray> TestResultsTableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[(int)TestResult::Role::Status] = "status";
    roles[(int)TestResult::Role::ClassName] = "className";
    roles[(int)TestResult::Role::TestName] = "testName";
    roles[(int)TestResult::Role::Message] = "message";

    return roles;
}


void TestResultsTableModel::parseFile(const QString &filepath)
{
    mTestResults.clear();

    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream ts(&file);
    QStringList lines;

    while (!ts.atEnd())
        lines.append(ts.readLine());

    for (const QString line : lines)
        parseLine(line);

    /*{
        TestResult t1;
        t1.status = TestResult::Status::Passed;
        t1.className = "Test_Rule";
        t1.testName = "initTestCase";
        t1.message = "";
        mTestResults.append(t1);
    }
    {
        TestResult t1;
        t1.status = TestResult::Status::Failed;
        t1.className = "Test_Rule";
        t1.testName = "makeIt";
        t1.message = "Bad pointer dude.";
        mTestResults.append(t1);
    }*/

    emit layoutChanged();
}


//returns character position where the testName ends in line
//TODO do all this with QRegularExpression later. I'm too dumb right now and need this tool ASAP.
TestResult parseClassNameAndTestName(const QString &line)
{
    TestResult testResult;

    int nameStartPos = line.indexOf(":")+2;
    int scopeResPos = line.indexOf("::")+2;
    int spaceAfterTestNamePos = line.indexOf(" ", scopeResPos);

#define INBOUNDS(pos) (pos > 0 && pos < line.count())

    if (INBOUNDS(nameStartPos) && INBOUNDS(scopeResPos))
    {
        testResult.className = line.mid(nameStartPos, scopeResPos-nameStartPos-2);
        testResult.testName = line.mid(scopeResPos, spaceAfterTestNamePos-scopeResPos);
    }

    if (INBOUNDS(spaceAfterTestNamePos))
        testResult.message = line.mid(spaceAfterTestNamePos);

#undef INBOUNDS

    return testResult;
}


void TestResultsTableModel::parseLine(const QString &line)
{
    if (line.startsWith("PASS   :"))
    {
        auto testResult = parseClassNameAndTestName(line);
        testResult.status = TestResult::Status::Passed;
        mTestResults.append(testResult);
    }
    else if (line.startsWith(("FAIL!  :")))
    {
        auto testResult = parseClassNameAndTestName(line);
        testResult.status = TestResult::Status::Failed;
        mTestResults.append(testResult);
    }
}
