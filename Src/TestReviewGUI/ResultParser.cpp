//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include <memory>

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
	const QString &dfmt = vbase::test::Results::dateFormat();

	treeItem->setProperty("dateTime_started",
						  QDateTime::fromString(rootObject["dateTime_started"].toString(),
						  dfmt));
    {
        QString v = rootObject["dateTime_finished"].toString();

        QDateTime dt = QDateTime::fromString(v, dfmt);
        treeItem->setProperty("dateTime_finished", QVariant(dt));
    }

    for (const auto &testClassResult : rootObject["results"].toArray())
		parseJsonObject_class(testClassResult.toObject(), treeItem);

    return true;
}


void ResultParser::parseJsonObject_class(const QJsonObject &classJsonObject,
										 QObject *treeItem)
{
	QObject *treeItemClass = new QObject(treeItem);
    treeItemClass->setProperty("type", "class");
	treeItemClass->setProperty("name", classJsonObject["className"].toString());

    //read all of the tests
	for (const auto &iter : classJsonObject["tests"].toArray())
    {
		parseJsonObject_test(iter.toObject(), treeItemClass);
    }

	//calculate totals
	int totalExecutionTime = 0;
	bool hasError = false;
	bool hasWarning = false;

	for (const QObject *child : treeItemClass->children())
	{
		totalExecutionTime += child->property("executionTime").toInt();

		//TODO please clean up all of thesee lose strings
		if (child->property("status").toString() == "error")
			hasError = true;
		else if (child->property("status").toString() == "warning")
			hasWarning = true;
	}

	QString status = "passed";

	if (hasError)
		status = "error";
	else if (hasWarning)
		status = "warning";

	treeItemClass->setProperty("status", status);
    treeItemClass->setProperty("executionTime", QVariant(totalExecutionTime));
}


void ResultParser::parseJsonObject_test(const QJsonObject &testJsonObject,
										QObject *parentClass)
{
	QObject *treeItemTest = new QObject(parentClass);
	treeItemTest->setProperty("type", "test");
	treeItemTest->setProperty("status", testJsonObject["status"].toString());
	treeItemTest->setProperty("name", testJsonObject["name"].toString());
	treeItemTest->setProperty("executionTime", testJsonObject["executionTime"].toInt());

	//go through all the messages
	for (const auto &failureIter : testJsonObject["messages"].toArray())
	{
		parseJsonObject_failure(failureIter.toObject(), treeItemTest);
	}
}


void ResultParser::parseJsonObject_failure(const QJsonObject &failureJsonObject,
										   QObject *parentTest)
{
	QObject *treeItemFailure = new QObject(parentTest);

	treeItemFailure->setProperty("type", "failure");

	vbase::test::Failure m;
	m.type = static_cast<vbase::test::Failure::Type>(failureJsonObject["type"].toInt());
	treeItemFailure->setProperty("failureType", m.typeName());

	treeItemFailure->setProperty("filePath", failureJsonObject["filePath"].toString());
	treeItemFailure->setProperty("lineNumber", failureJsonObject["lineNumber"].toInt());

	QStringList messages;
	for (auto varient : failureJsonObject["details"].toArray().toVariantList())
		messages.append(varient.toString());

	treeItemFailure->setProperty("details", messages);
}
