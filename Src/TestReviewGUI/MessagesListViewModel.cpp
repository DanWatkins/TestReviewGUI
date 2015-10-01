//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include "MessagesListViewModel.h"

//
// # public #
//

MessagesListViewModel::MessagesListViewModel(QObject *parent) :
	QAbstractListModel(parent)
{
}

void MessagesListViewModel::setTestIndex(const QModelIndex &testIndex)
{
	QAbstractListModel::beginResetModel();
	{
		mTestObject = static_cast<QObject*>(testIndex.internalPointer());
	}
	QAbstractListModel::endResetModel();
}


int MessagesListViewModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	if (!mTestObject)
		return 0;

	return mTestObject->children().count();
}


QHash<int, QByteArray> MessagesListViewModel::roleNames() const
{
	QHash<int, QByteArray> roles;
	roles[static_cast<int>(Roles::FilePath)] = "filePath";
	roles[static_cast<int>(Roles::LineNumber)] = "lineNumber";
	roles[static_cast<int>(Roles::Details)] = "details";

	return roles;
}


QVariant MessagesListViewModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	QObject *detailChild = mTestObject->children().at(index.row());
	Roles roleEnum = static_cast<Roles>(role);

	switch (roleEnum)
	{
	case Roles::FilePath:
		return detailChild->property("filePath");
	case Roles::LineNumber:
		return detailChild->property("lineNumber");
	case Roles::Details:
		return  detailChild->property("details");
	}

	return QVariant("");
}

