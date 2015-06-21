#ifndef TestResultsTableModel_h
#define TestResultsTableModel_h

#include <QAbstractTableModel>
#include "TestResult.h"

class TestResultsTableModel : public QAbstractTableModel
{
public:
    TestResultsTableModel();

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addTestResult(const TestResult &testResult) { mTestResults.append(testResult); }

private:
    QVector<TestResult> mTestResults;
};

#endif
