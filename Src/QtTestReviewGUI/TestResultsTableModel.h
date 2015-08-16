//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#ifndef TestResultsTableModel_h
#define TestResultsTableModel_h

#include <QAbstractTableModel>
#include "TestResult.h"

class FriendParser;

class TestResultsTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    friend class ResultParser;
    TestResultsTableModel(QObject *parent=nullptr);

    ~TestResultsTableModel() { qDebug() << "Destroyed TestResultsTableModel"; }

    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    QVector<TestResult*>& testResults() { return mTestResults; }
    Q_INVOKABLE void parseFile(const QString &filepath);
    Q_INVOKABLE void gotoSourceFileForRow(int row);

    QString statusText() const;

signals:
    statusTextChanged();

private:
    QVector<TestResult*> mTestResults;


};

#endif
