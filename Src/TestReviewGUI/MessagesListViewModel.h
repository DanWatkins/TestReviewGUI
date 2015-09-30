//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#ifndef MessagesListViewModel_h
#define MessagesListViewModel_h

#include <QtCore/QAbstractListModel>

#include "TreeItem.h"

class MessagesListViewModel : public QAbstractListModel
{
    Q_OBJECT

public:
    friend class ResultParser;
	MessagesListViewModel(QObject *parent=nullptr);

	//TODO maybe just get Message, TestResult, and Class all QObject derived?
	Q_INVOKABLE void setTestIndex(const QModelIndex &testResultIndex);

	int rowCount(const QModelIndex &parent) const override;
	QHash<int, QByteArray> roleNames() const override;
	QVariant data(const QModelIndex &index, int role) const override;

private:
	enum class Roles
    {
		Type = Qt::UserRole + 10,
		FilePath,
		LineNumber,
		Details
    };
};



#endif
