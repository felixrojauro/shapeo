#include <QGuiApplication>
#include <QDebug>
// android
#include <QAndroidJniObject>
#include <QtAndroid>

#include "cqmlmainviewframe.h"
#include "common.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	MyCommon *pCommon = new MyCommon();
	CQmlMainViewFrame view;
	view.registerCustomQMLTypes();
	view.rootContext()->setContextProperty("MyCommon", pCommon);
	view.setSource(QUrl("qrc:/qml/QmlMainViewFrame.qml"));
	view.Initialize();
	view.show();

    return app.exec();
}


