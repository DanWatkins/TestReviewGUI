#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "TestResultsTableModel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //TestResultsTableModel testResultsTableModel;
    //engine.rootContext()->setContextProperty("testResultsTableModel", &testResultsTableModel);

    qmlRegisterType<TestResultsTableModel>("QtTestReviewGUI", 1, 0, "TestResultsTableModel");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
