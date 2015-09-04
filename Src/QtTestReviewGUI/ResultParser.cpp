//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include <QtCore/QFile>
#include <QtCore/QUrl>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include "ResultParser.h"

bool ResultParser::parseFile(const QString &filepath, TreeItem *treeItem)
{
    //QUrl(filepath).toLocalFile()
    auto cleanFilePath = filepath;
    cleanFilePath.replace("file:///", "");
    QFile file(cleanFilePath);

    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;

    QJsonParseError error;
    auto doc = QJsonDocument::fromJson(file.readAll(), &error);

    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << error.errorString();
        return false;
    }

    for (const auto &testClassResult : doc.array())
        parseTestClassJsonObject(testClassResult.toObject(), treeItem);

    return true;
}


void ResultParser::parseTestClassJsonObject(
        const QJsonObject &testClassJsonObject, TreeItem *treeItem)
{
    auto *treeItemClass = new TreeItem_Class(treeItem);
    treeItemClass->pName = testClassJsonObject["className"].toString();

    for (const auto &iter : testClassJsonObject["results"].toArray())
    {
        auto testResultJsonObject = iter.toObject();
        auto *treeItemTest = new TreeItem_Test(treeItemClass);

        treeItemTest->pStatus = testResultJsonObject["status"].toString();
        treeItemTest->pName = testResultJsonObject["name"].toString();

        qDebug() << "Parsed test " << treeItemTest->pName();

        //FIXME
//        if (testResult->status == TestResult::Status::Failed)
//        {
//            testResult->filePath = testResultJsonObject["filePath"].toString();
//            testResult->fileLineNumber = testResultJsonObject["lineNumber"].toInt();
//        }
    }
}
