//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include "TestResultsTableModel.h"

#include <QtCore/QDebug>
#include <QtCore/QProcess>

#include "Appstate.h"
#include "ResultParser.h"

//
// # public #
//

TestResultsTableModel::TestResultsTableModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    //TODO massive hack YO
    if (Appstate::openFilePath != "")
        parseFile(Appstate::openFilePath);
}

int TestResultsTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    //FIXME
    return 0;
    //return mTestResults.size();
}


int TestResultsTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}


QHash<int, QByteArray> TestResultsTableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::Status)] = "status";
    roles[static_cast<int>(Roles::Test)] = "test";

    return roles;
}


QVariant TestResultsTableModel::data(const QModelIndex &index, int role) const
{
//    const auto testResult = mTestResults[index.row()];

//    switch (static_cast<TestResult::Role>(role))
//    {
//    case Roles::Status:
//        return testResult->statusAsString();
//    case Roles::Test:
//        return testResult->className;
//    }

    //FIXME

    return QVariant::Invalid;
}


QVariant TestResultsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return QVariant("Hello");
    //TODO

    return QVariant();
}


Qt::ItemFlags TestResultsTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}


QModelIndex TestResultsTableModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    //this is a class node
    if (!parent.isValid())
    {
        //FIXME
        createIndex(row, column, nullptr);
    }
    //this is a test node
    else
    {
        //FIXME
        createIndex(row, column, nullptr);
    }
}


QModelIndex TestResultsTableModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    if (child.parent().internalPointer() == nullptr)
        return QModelIndex();
    else
    {
        //FIXME
        return QModelIndex();
    }
}


void TestResultsTableModel::parseFile(const QString &filepath)
{
    ResultParser parser;
    parser.parseFile(filepath, &mTestResultsMap);

    emit layoutChanged();
    emit statusTextChanged();
}


void TestResultsTableModel::gotoSourceFileForRow(int row)
{
    //FIXME

//    if (mTestResults.count() <= row)
//        return;

//    const TestResult *testResult = mTestResults[row];

//    QProcess process;
//    QStringList arguments;
//    arguments << testResult->filePath + ":"
//                 + QString::number(testResult->fileLineNumber) << "-client";
//    process.start("qtcreator.exe", arguments);
//    //TODO don't use EXE for crossplatform compatability
//    process.waitForFinished();
}


QString TestResultsTableModel::statusText() const
{
    /*auto testCountForStatus = [this](TestResult::Status status)
    {
        int count = 0;

        for (const TestResult *testResult : mTestResults)
            if (testResult->status == status)
                count++;

        return count;
    };

    QString statusText;
    statusText +=
        QString::number(testCountForStatus(TestResult::Status::Passed))
            + " passed, ";
    statusText +=
        QString::number(testCountForStatus(TestResult::Status::Failed))
            + " failed, ";
    statusText +=
        QString::number(testCountForStatus(TestResult::Status::Skipped))
            + " skipped, ";
    statusText +=
        QString::number(testCountForStatus(TestResult::Status::Blacklisted))
            + " blacklisted";

    return statusText;*/

    //FIXME

    return "";
}

//
// # private #
//
