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

bool ResultParser::parseFile(const QString &filepath,
                             TestResultsMap *testResultsMap)
{
    mTestResultsMap = testResultsMap;

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
        parseTestClassJsonObject(testClassResult.toObject());

    return true;
}


TestResult::Status statusForString(const QString &str)
{
    if (str == "failed")
        return TestResult::Status::Failed;
    else if (str == "passed")
        return TestResult::Status::Passed;

    return TestResult::Status::None;
}


void ResultParser::parseTestClassJsonObject(const QJsonObject &testClassJsonObject)
{
    QVector<TestResult*> testResults;

    for (const auto &iter : testClassJsonObject["results"].toArray())
    {
        auto testResultJsonObject = iter.toObject();
        auto *testResult = new TestResult;

        testResult->status = statusForString(testResultJsonObject["status"].toString());
        testResult->testName = testResultJsonObject["name"].toString();

        qDebug() << "Parsed test " << testResult->testName;

        if (testResult->status == TestResult::Status::Failed)
        {
            testResult->filePath = testResultJsonObject["filePath"].toString();
            testResult->fileLineNumber = testResultJsonObject["lineNumber"].toInt();
        }

        testResults.append(testResult);
    }

    mTestResultsMap->insert(testClassJsonObject["className"].toString(), testResults);
}
