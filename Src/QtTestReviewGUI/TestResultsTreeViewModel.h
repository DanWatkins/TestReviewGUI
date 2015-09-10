//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#ifndef TestResultsTableModel_h
#define TestResultsTableModel_h

#include <QtCore/QAbstractItemModel>
#include <QtCore/QMap>
#include <QtCore/QScopedPointer>

#include "TreeItem.h"

class TestResultsTreeViewModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    friend class ResultParser;
    TestResultsTreeViewModel(QObject *parent=nullptr);

    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE void parseFile(const QString &filepath);
    Q_INVOKABLE bool gotoSourceFileForRow(const QModelIndex &index);

    QString statusText() const;

signals:
    void statusTextChanged();

private:
    QObject *mRootTreeItem;

    enum class Roles
    {
        Class = Qt::UserRole + 10,
        Test,
        Status,
        ExecutionTime
    };
};

#endif
