//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include <QtCore/QProcess>

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


void MessagesListViewModel::gotoSourceFileForRow(int row) const
{
	if (mTestObject->children().count() <= row)
		return;

	QObject *item = mTestObject->children().at(row);

	if (item->property("type").toString() == "failure")
	{
		const QVariant &filePath = item->property("filePath");
		const QVariant &lineNumber = item->property("lineNumber");

		if (filePath.isValid() && lineNumber.isValid())
		{
			QProcess process;
			QStringList arguments;
			arguments << filePath.toString() + ":"
						 + lineNumber.toString() << "-client";

			//TODO remove hardcoding
			process.start("C:/Qt/Tools/QtCreator/bin/qtcreator.exe", arguments);
			process.waitForFinished();
		}
	}
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
	roles[static_cast<int>(Roles::FailureType)] = "failureType";

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
	case Roles::FailureType:
		return detailChild->property("failureType");
	}

	return QVariant("");
}

