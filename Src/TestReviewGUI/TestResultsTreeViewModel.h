//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#ifndef TestResultsTableModel_h
#define TestResultsTableModel_h

#include <QtCore/QAbstractItemModel>
#include <QtCore/QMap>
#include <QtCore/QScopedPointer>
#include <QtCore/QDateTime>

#include <QQmlEngine>

#include "TreeItem.h"

class TestResultsTreeViewModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    friend class ResultParser;
    TestResultsTreeViewModel(QObject *parent=nullptr);

    Q_PROPERTY(QString statusText READ statusText NOTIFY fileParsed)
    Q_PROPERTY(QDateTime dateTime_started READ dateTime_started NOTIFY fileParsed)
    Q_PROPERTY(QDateTime dateTime_finished READ dateTime_finished NOTIFY fileParsed)

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &index) const override;

	Q_INVOKABLE QVariant internalProperty(const QModelIndex &index, const QString &property) const;
    Q_INVOKABLE void parseFile(const QString &filepath);

    QString statusText() const;
    QDateTime dateTime_started() const { return mRootTreeItem->property("dateTime_started").toDateTime(); }
	QDateTime dateTime_finished() const { return mRootTreeItem->property("dateTime_finished").toDateTime(); }

signals:
    void fileParsed();

private:
    QObject *mRootTreeItem;

	//TODO transition these to actual settings
	bool mShowFailedTests = true;
	bool mShowWarnedTests = true;
	bool mShowPassedTests = true;

    enum class Roles
    {
		Name = Qt::UserRole + 10,
		Status,
        ExecutionTime
    };
};



#endif
