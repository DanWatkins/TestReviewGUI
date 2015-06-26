#ifndef TestResultsTableModel_h
#define TestResultsTableModel_h

#include <QAbstractTableModel>
#include "TestResult.h"

class TestResultsTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TestResultsTableModel();

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVector<TestResult>& testResults() { return mTestResults; }
    Q_INVOKABLE void parseFile(const QString &filepath);

private:
    QVector<TestResult> mTestResults;
};

#endif
