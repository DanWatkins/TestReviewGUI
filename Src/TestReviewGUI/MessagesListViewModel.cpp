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
		mTopLevelObject = static_cast<QObject*>(testIndex.internalPointer());
	}
	QAbstractListModel::endResetModel();
}


void MessagesListViewModel::gotoSourceFileForRow(int row) const
{
	const QObject *item = testObjectForRow(row);

	if (item && item->property("type").toString() == "failure")
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

	if (!mTopLevelObject)
		return 0;

	QString type = mTopLevelObject->property("type").toString();

	if (type == "class")
	{
		int count = 0;

		for (const QObject *child : mTopLevelObject->children())
			count += child->children().count();

		return count;
	}
	else if (type == "test")
	{
		return mTopLevelObject->children().count();
	}

	return 0;
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

	const QObject *detailChild = testObjectForRow(index.row());
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


const QObject* MessagesListViewModel::testObjectForRow(int row) const
{
	QString type = mTopLevelObject->property("type").toString();

	if (type == "class")
	{
		int index = 0;

		for (const QObject *child : mTopLevelObject->children())
		{
			for (int i=0; i<child->children().count(); i++)
			{
				if (index == row)
				{
					return child->children().at(i);
				}

				index++;
			}
		}
	}
	else if (type == "test")
	{
		return mTopLevelObject->children().at(row);
	}

	return nullptr;
}

