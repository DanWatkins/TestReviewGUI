#include "TestResultsTableModel.h"
#include <QDebug>

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

    {
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
    }

    emit layoutChanged();
}
