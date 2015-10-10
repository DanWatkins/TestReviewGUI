//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#ifndef MessagesListViewModel_h
#define MessagesListViewModel_h

#include <QtCore/QAbstractListModel>

#include "TreeItem.h"

class FailuresListViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    friend class ResultParser;
	FailuresListViewModel(QObject *parent=nullptr);

	Q_INVOKABLE void setTopLevelIndex(const QModelIndex &topLevelIndex);
	Q_INVOKABLE void gotoSourceFileForRow(int row) const;

	int rowCount(const QModelIndex &parent=QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	QVariant data(const QModelIndex &index, int role) const override;

private:
	enum class Roles
    {
		FilePath = Qt::UserRole + 10,
		LineNumber,
		Details,
		FailureType
    };

	const QObject *mTopLevelObject = nullptr;

	const QObject* testObjectForRow(int row) const;
};

#endif
