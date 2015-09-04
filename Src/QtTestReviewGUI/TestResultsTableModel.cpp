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
    QAbstractItemModel(parent),
    mRootTreeItem(new TreeItem(this))
{
    //TODO massive hack YO
    if (Appstate::openFilePath != "")
        parseFile(Appstate::openFilePath);
}


int TestResultsTableModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}


int TestResultsTableModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}


QHash<int, QByteArray> TestResultsTableModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    return roles;
}


QVariant TestResultsTableModel::data(const QModelIndex &index, int role) const
{
    return int();
}


QVariant TestResultsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}


QModelIndex TestResultsTableModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}


QModelIndex TestResultsTableModel::parent(const QModelIndex &child) const
{

}


void TestResultsTableModel::parseFile(const QString &filepath)
{
    ResultParser parser;
    parser.parseFile(filepath, mRootTreeItem.data());

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
