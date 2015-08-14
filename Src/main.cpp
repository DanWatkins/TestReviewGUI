#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include <windows.h>

#include "TestResultsTableModel.h"
#include "Appstate.h"

int main(int argc, char *argv[])
{
    qDebug() << "Arguments:";

    for (int i=0; i<argc; i++)
        qDebug() << argv[i];

    if (argc >= 2)
    {
        Appstate::openFilePath = QString("file:///") + argv[1];
    }

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<TestResultsTableModel>("QtTestReviewGUI", 1, 0, "TestResultsTableModel");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
