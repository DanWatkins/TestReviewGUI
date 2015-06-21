#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "TestResultsTableModel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    TestResultsTableModel testResultsTableModel;
    {
        TestResult t1;
        t1.status = TestResult::Status::Passed;
        t1.className = "Test_Rule";
        t1.testName = "initTestCase";
        t1.message = "";
        testResultsTableModel.addTestResult(t1);
    }
    {
        TestResult t1;
        t1.status = TestResult::Status::Failed;
        t1.className = "Test_Rule";
        t1.testName = "makeIt";
        t1.message = "Bad pointer dude.";
        testResultsTableModel.addTestResult(t1);
    }

    engine.rootContext()->setContextProperty("testResultsTableModel", &testResultsTableModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
