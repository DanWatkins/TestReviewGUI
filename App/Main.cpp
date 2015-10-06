//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtCore/QWaitCondition>
#include <QtConcurrent/QtConcurrent>

#include <ValpineBase/ValpineBase.h>
#include <ValpineBase/SingleInstance.h>
#include <ValpineBase/Settings.h>

#include <TestReviewGUI/TestResultsTreeViewModel.h>
#include <TestReviewGUI/FailuresListViewModel.h>
#include <TestReviewGUI/Appstate.h>
#include <TestReviewGUI/Settings.h>

vbase::Settings<Settings> appSettings;

void registerQmlTypes(QQmlEngine &engine)
{
	vbase::ValpineBase::registerQmlModule(&engine);

	qmlRegisterType<vbase::SettingsBase>("TestReviewGUI", 1, 0, "Settings");

	qmlRegisterType<Settings>("TestReviewGUI", 1, 0, "SettingsEnum");

	qmlRegisterType<TestResultsTreeViewModel>("TestReviewGUI", 1, 0,
											  "TestResultsTreeViewModel");

	qmlRegisterType<FailuresListViewModel>("TestReviewGUI", 1, 0,
										   "FailuresListViewModel");
}


int main(int argc, char *argv[])
{
	qDebug() << "Arguments:";

	for (int i=0; i<argc; i++)
		qDebug() << argv[i];

	QApplication app(argc, argv);
	app.setApplicationVersion("0.8.0");	//TODO clean up
	appSettings.load("TestReviewGUI.ini");

	QString appFullName = "com.danwatkins.testreviewgui";
	vbase::SingleInstance singleInstance;

	//ensure we are only running a single instance
	{
		if (singleInstance.hasPrevious(appFullName, QApplication::arguments()))
			return 0;

		singleInstance.listen(appFullName);
	}


	QQmlApplicationEngine engine;
	registerQmlTypes(engine);

	//set various context properties
	{
		engine.rootContext()->setContextProperty("appVersion", app.applicationVersion());
		engine.rootContext()->setContextProperty("appSettings", &appSettings);
		engine.rootContext()->setContextProperty("appSingleInstance", &singleInstance);

		QString openFilepath = (argc >= 2) ? QString("file:///") + argv[1] : "";
		engine.rootContext()->setContextProperty("openFilepath", openFilepath);
	}

	engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

	return app.exec();
}
