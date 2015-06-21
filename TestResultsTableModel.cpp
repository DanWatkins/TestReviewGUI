#include "TestResultsTableModel.h"
#include <QDebug>

TestResultsTableModel::TestResultsTableModel()
{

}

int TestResultsTableModel::rowCount(const QModelIndex &parent) const
{
    mTestResults.count();
}


int TestResultsTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}


QVariant TestResultsTableModel::data(const QModelIndex &index, int role) const
{
    const TestResult &testResult = mTestResults[index.row()];
    int column = index.column(); //index.column();

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
