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
	QObject *obj = static_cast<QObject*>(testIndex.internalPointer());

	if (!obj)
		qDebug() << "Oh shit";
	else
	{
		qDebug() << "Test";
		qDebug() << obj->property("type").toString();
		qDebug() << obj->property("status").toString();
		qDebug() << obj->property("name").toString();
		qDebug() << obj->property("executionTime").toString();

		for (QObject *child : obj->children())
		{
			qDebug() << "Child...";
			qDebug() << "   " << child->property("filePath");
			qDebug() << "   " << child->property("lineNumber");
			qDebug() << "   " << child->property("details").toStringList();
		}
	}
}


int MessagesListViewModel::rowCount(const QModelIndex &parent) const
{
	return 0;
}


QHash<int, QByteArray> MessagesListViewModel::roleNames() const
{

}


QVariant MessagesListViewModel::data(const QModelIndex &index, int role) const
{

}

