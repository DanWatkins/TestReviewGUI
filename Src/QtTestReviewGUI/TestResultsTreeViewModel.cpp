//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include "TestResultsTreeViewModel.h"

#include <QtCore/QDebug>
#include <QtCore/QProcess>

#include "Appstate.h"
#include "ResultParser.h"

//
// # public #
//

TestResultsTreeViewModel::TestResultsTreeViewModel(QObject *parent) :
    QAbstractItemModel(parent),
    mRootTreeItem(new QObject(this))
{
    //TODO massive hack YO
    if (Appstate::openFilePath != "")
        parseFile(Appstate::openFilePath);
}


int TestResultsTreeViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    QObject *item;

    if (!parent.isValid())
        item = mRootTreeItem;
    else
	{
		item = static_cast<QObject*>(parent.internalPointer());

		if (item->property("type").toString() == "class")
		{
			int count = 0;

			for (auto child : item->children())
			{
				QString status = child->property("status").toString();

				if ((mShowFailedTests && status == "failed") ||
					(mShowPassedTests && status == "passed"))
				{
					count++;
				}
			}

			return count;
		}
	}

	if (item->property("type").toString() == "test")
		return 0;

	return item->children().count();
}


int TestResultsTreeViewModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}


QHash<int, QByteArray> TestResultsTreeViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::Class)] = "class";
    roles[static_cast<int>(Roles::Test)] = "test";
    roles[static_cast<int>(Roles::Status)] = "status";
    roles[static_cast<int>(Roles::ExecutionTime)] = "executionTime";

    return roles;
}


QVariant TestResultsTreeViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QObject *item = static_cast<QObject*>(index.internalPointer());

    switch (static_cast<Roles>(role))
    {
    case Roles::Class:
        if (item->property("type") == QString("class"))
            return item->property("name");
        break;

    case Roles::Test:
        if (item->property("type") == QString("test"))
            return item->property("name");
        break;

    case Roles::Status:
        if (item->property("type") == QString("test"))
            return item->property("status");
        break;

    case Roles::ExecutionTime:
		return item->property("executionTime");
        break;
    }

    return QVariant("");
}


QModelIndex TestResultsTreeViewModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    QObject *parentItem;

    if (!parent.isValid())
        parentItem = mRootTreeItem;
    else
        parentItem = static_cast<QObject*>(parent.internalPointer());

	if (parentItem->property("type").toString() == "class")
	{
		int effectiveRow = -1;

		for (auto child : parentItem->children())
		{
			QString status = child->property("status").toString();

			if ((mShowFailedTests && status == "failed") ||
				(mShowPassedTests && status == "passed"))
			{
				effectiveRow++;
			}

			if (effectiveRow == row)
				return createIndex(row, column, child);
		}
	}
	else
	{
		QObject *childItem = parentItem->children().at(row);

		if (childItem)
		{
			return createIndex(row, column, childItem);
		}
	}

	return QModelIndex();
}


QModelIndex TestResultsTreeViewModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    auto *childItem = static_cast<QObject*>(index.internalPointer());
    auto *parentItem = childItem->parent();

    if (parentItem == mRootTreeItem)
        return QModelIndex();

    int row = parentItem->parent()->children().indexOf(parentItem);

    return createIndex(row, 0, parentItem);
}


QVariant TestResultsTreeViewModel::TestResultsTreeViewModel::internalProperty(const QModelIndex&index, const QString&property) const
{
	if (!index.isValid())
		return QVariant("");

	return static_cast<QObject*>(index.internalPointer())->property(property.toStdString().c_str());
}


void TestResultsTreeViewModel::parseFile(const QString &filepath)
{
	QAbstractItemModel::beginResetModel();

	if (mRootTreeItem)
		delete mRootTreeItem;

	mRootTreeItem = new QObject(this);

	ResultParser parser;
	parser.parseFile(filepath, mRootTreeItem);

	emit fileParsed();

    QAbstractItemModel::endResetModel();
}


bool TestResultsTreeViewModel::gotoSourceFileForRow(const QModelIndex &index)
{
    auto item = static_cast<QObject*>(index.internalPointer());

    if (item->property("type").toString() == "test")
    {
        const QVariant &filePath = item->property("filePath");
        const QVariant &fileLineNumber = item->property("fileLineNumber");

        if (filePath.isValid() && fileLineNumber.isValid())
        {
            QProcess process;
            QStringList arguments;
            arguments << filePath.toString() + ":"
                         + fileLineNumber.toString() << "-client";

            //TODO remove hardcoding
            process.start("C:/Qt/Tools/QtCreator/bin/qtcreator.exe", arguments);
            process.waitForFinished();
        }
        else
            return false;
    }

    return true;
}


QString TestResultsTreeViewModel::statusText() const
{
    auto sumStatuses = [this] (const QString &status) -> int
    {
        int count = 0;

        for (const QObject *child : mRootTreeItem->children())
        {
            for (const QObject *test : child->children())
            {
                if (test->property("status") == status)
                    count++;
            }
        }

        return count;
    };

    QString statusText;
    statusText +=
        QString::number(sumStatuses("passed")) + " passed, ";
    statusText +=
        QString::number(sumStatuses("failed")) + " failed, ";
    statusText +=
        QString::number(sumStatuses("skipped")) + " skipped";

    return statusText;
}



//
// # private #
//
