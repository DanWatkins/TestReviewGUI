//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include <ValpineBase/ValpineBase.h>

#include <QtTestReviewGUI/TestResultsTreeViewModel.h>
#include <QtTestReviewGUI/Appstate.h>

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
	app.setApplicationVersion("0.8.0");	//TODO clean up

    QQmlApplicationEngine engine;
    ValpineBase::registerQmlModule(&engine);
    qmlRegisterType<TestResultsTreeViewModel>("QtTestReviewGUI", 1, 0, "TestResultsTreeViewModel");

	engine.rootContext()->setContextProperty("appVersion", app.applicationVersion());

    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    return app.exec();
}
