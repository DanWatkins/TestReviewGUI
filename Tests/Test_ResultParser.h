//=============================================================================|
// Copyright (C) 2015 Valpineware
// This file is licensed under the MIT License.
//=============================================================================|

#include <QObject>
#include <ValpineBase/Test.h>
#include <QtTestReviewGUI/ResultParser.h>
#include <memory>

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


//    std::unique_ptr<TestResultsTableModel> makeModel(const QString &filepath)
//    {
//        ResultParser parser;
//        auto model = std::make_unique<TestResultsTableModel>();
//        parser.parseFile(filepath, model.get());

//        return model;
//    }


private slots:
    //Standard, all passed
    //FIXME
//    void Results_01()
//    {
//        auto model = makeModel("://FakeResults/Results_01.txt");
//        const auto &results = model->testResults();
//        QCOMPARE(results.count(), 3);

//        assertTestResult(results[0], TestResult::Status::Passed,
//                         "Test_Loadable", "simpleCheck", "", "", 0);
//        assertTestResult(results[1], TestResult::Status::Passed,
//                        "Test_Loadable", "cleanupTestCase", "", "", 0);
//        assertTestResult(results[2], TestResult::Status::Passed,
//                        "QObject", "initTestCase", "", "", 0);
//    }


//    //QVERIFY_EXCEPTION_THROWN
//    void Results_02()
//    {
//        auto model = makeModel("://FakeResults/Results_02.txt");
//        const auto &results = model->testResults();
//        QCOMPARE(results.count(), 3);

//        assertTestResult(results[1], TestResult::Status::Failed,
//            "Test_ResultParser", "Results_QWARN",
//            "Expected exception of type std::exception to be thrown but no exception caught",
//            "E:/GoogleDrive/Code/Dev/DanWatkins/QtTestReviewGUI/Tests/Test_ResultParser.h",
//            59);
//    }


//    //QVERIFY
//    void Results_03()
//    {
//        auto model = makeModel("://FakeResults/Results_03.txt");
//        const auto &results = model->testResults();
//        QCOMPARE(results.count(), 3);

//        assertTestResult(results[1], TestResult::Status::Failed,
//            "Bogus", "Results_03", "'false' returned FALSE. ()",
//            "E:/Bogusnator/Bogus.h", 79);
//    }


//    void Results_QSKIP()
//    {
//        auto model = makeModel("://FakeResults/Results_QSKIP.txt");
//        const auto &results = model->testResults();
//        QCOMPARE(results.count(), 1);

//        assertTestResult(results[0], TestResult::Status::Skipped,
//            "Nalgene", "doStuffForXPOnly", "Not running on Windows XP",
//            "E:/Code/Nalegene.h", 94);
//    }
};

DECLARE_TEST(Test_ResultParser)
