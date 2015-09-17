//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include <ValpineBase/ValpineBase.h>
#include <ValpineBase/SingleInstance.h>

#include <QtTestReviewGUI/TestResultsTreeViewModel.h>
#include <QtTestReviewGUI/Appstate.h>

int main(int argc, char *argv[])
{
    qDebug() << "Arguments:";

    for (int i=0; i<argc; i++)
        qDebug() << argv[i];

    QApplication app(argc, argv);
    app.setApplicationVersion("0.8.0");	//TODO clean up

    QString appFullName = "com.danwatkins.testreviewgui";
    vbase::SingleInstance singleInstance;

    if (singleInstance.hasPrevious(appFullName, QApplication::arguments()))
    {
		qDebug() << "Previous instance found";
		return 0;
    }
    else
    {
		qDebug() << "This is the only instance";
    }

	singleInstance.listen(appFullName);

    QQmlApplicationEngine engine;
    ValpineBase::registerQmlModule(&engine);
    qmlRegisterType<TestResultsTreeViewModel>("QtTestReviewGUI", 1, 0, "TestResultsTreeViewModel");

    //set various context properties
    {
	    engine.rootContext()->setContextProperty("appVersion", app.applicationVersion());

	    QString openFilepath = (argc >= 2) ? QString("file:///") + argv[1] : "";
	    engine.rootContext()->setContextProperty("openFilepath", openFilepath);
    }

    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    return app.exec();
}
