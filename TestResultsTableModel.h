#ifndef TestResultsTableModel_h
#define TestResultsTableModel_h

#include <QAbstractTableModel>
#include "TestResult.h"

class TestResultsTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TestResultsTableModel();

    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    QVector<TestResult*>& testResults() { return mTestResults; }
    Q_INVOKABLE void parseFile(const QString &filepath);
    Q_INVOKABLE void gotoSourceFile(const QString &filepath, int lineNumber);

    QString statusText() const;

signals:
    statusTextChanged();

private:
    QVector<TestResult*> mTestResults;

    TestResult* parseLine(const QString &line);
    TestResult* parseClassNameAndTestName(const QString &line);
};

#endif
