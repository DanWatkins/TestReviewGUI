//=============================================================================|
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//=============================================================================|

#include <QObject>
#include <ValpineBase/Test.h>
#include <QtTestReviewGUI/ResultParser.h>

class Test_ResultParser : public QObject
{
    Q_OBJECT

private:
    void assertTestResult(const TestResult *testResult,
                          TestResult::Status status,
                          const QString &className,
                          const QString &testName,
                          const QString &message,
                          const QString &filePath,
                          int fileLineNumber)
    {
        QCOMPARE(testResult->status, status);
        QCOMPARE(testResult->className, className);
        QCOMPARE(testResult->testName, testName);
        QCOMPARE(testResult->message, message);
        QCOMPARE(testResult->filePath, filePath);
        QCOMPARE(testResult->fileLineNumber, fileLineNumber);
    }

private slots:
    void Results_01()
    {
        ResultParser parser;
        TestResultsTableModel model;
        parser.parseFile("://FakeResults/Results_01.txt", &model);


        const auto& results = model.testResults();

        QCOMPARE(results.count(), 3);

        assertTestResult(results[0], TestResult::Status::Passed,
                         "Test_Loadable", "simpleCheck", "", "", 0);
        assertTestResult(results[1], TestResult::Status::Passed,
                        "Test_Loadable", "cleanupTestCase", "", "", 0);
        assertTestResult(results[2], TestResult::Status::Passed,
                        "QObject", "initTestCase", "", "", 0);
    }
};

DECLARE_TEST(Test_ResultParser)
