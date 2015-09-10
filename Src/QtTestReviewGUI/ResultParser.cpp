//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include <QtCore/QFile>
#include <QtCore/QUrl>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QDateTime>

#include <ValpineBase/Test/Suite.h>

#include "ResultParser.h"

bool ResultParser::parseFile(const QString &filepath, QObject *treeItem)
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

    const QJsonObject rootObject = doc.object();
    auto dateTime_started = QDateTime::fromString(rootObject["dateTime_started"].toString(),
            vbase::test::Suite::dateFormat());

    auto dateTime_finished = QDateTime::fromString(rootObject["dateTime_finished"].toString(),
            vbase::test::Suite::dateFormat());

    for (const auto &testClassResult : rootObject["results"].toArray())
        parseTestClassJsonObject(testClassResult.toObject(), treeItem);

    return true;
}


void ResultParser::parseTestClassJsonObject(
        const QJsonObject &testClassJsonObject, QObject *treeItem)
{
    auto *treeItemClass = new QObject(treeItem);
    treeItemClass->setProperty("type", "class");
    treeItemClass->setProperty("name", testClassJsonObject["className"].toString());

    for (const auto &iter : testClassJsonObject["results"].toArray())
    {
        auto testResultJsonObject = iter.toObject();
        auto *treeItemTest = new QObject(treeItemClass);

        treeItemTest->setProperty("type", "test");
        treeItemTest->setProperty("status", testResultJsonObject["status"].toString());
        treeItemTest->setProperty("name", testResultJsonObject["name"].toString());
        treeItemTest->setProperty("executionTime", testResultJsonObject["executionTime"].toString());

        //FIXME
        if (treeItemTest->property("status").toString() == "failed")
        {
            treeItemTest->setProperty("filePath", testResultJsonObject["filePath"].toString());
            treeItemTest->setProperty("fileLineNumber", testResultJsonObject["lineNumber"].toInt());

            treeItemTest->setProperty("message", testResultJsonObject["message"].toArray());
        }
    }
}
