//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#ifndef TestResultsTableModel_h
#define TestResultsTableModel_h

#include <QtCore/QAbstractItemModel>
#include <QtCore/QMap>

#include "TestResult.h"

class TestResultsTableModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    friend class ResultParser;
    TestResultsTableModel(QObject *parent=nullptr);

    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)

    enum class Roles
    {
        Status = Qt::UserRole + 10,
        Test
    };

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    Q_INVOKABLE void parseFile(const QString &filepath);
    Q_INVOKABLE void gotoSourceFileForRow(int row);

    QString statusText() const;

signals:
    void statusTextChanged();

private:
    //map of class names and the test results
    TestResultsMap mTestResultsMap;
};

#endif
