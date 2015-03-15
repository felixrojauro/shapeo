#include "cqmlmainviewframe.h"
#include <unistd.h>

// android
#include <QtAndroid>

#include "cqmlmainview.h"

#include "cqmlslider.h"

#include "cqmlviewbase.h"
#include "cqmlviewems.h"
#include "cqmlviewgalwan.h"
#include "cqmlviewvacuum.h"
#include "cqmlimagebutton.h"
#include "cqmltextbutton.h"
#include "common.h"
CQmlMainViewFrame::CQmlMainViewFrame(QQuickView *parent)
	: QQuickView(parent)
	, m_bFirstConnectionAttemptFinished( false )
{
}

CQmlMainViewFrame::~CQmlMainViewFrame()
{
	clearScreenOnFlags();
}

void CQmlMainViewFrame::registerCustomQMLTypes()
{
    qmlRegisterType<CQmlMainView>("MyCustoms", 1, 0, "CQmlMainView");
	qmlRegisterType<MyCommon>("MyCustoms", 1, 0, "MyQMLEnums");

	qmlRegisterType<CQmlSlider>("MyCustoms", 1, 0, "CQmlSlider");
	qmlRegisterType<CQmlTextButton>("MyCustoms", 1, 0, "CQmlTextButton");
	qmlRegisterType<CQmlImageButton>("MyCustoms", 1, 0, "CQmlImageButton");

	qmlRegisterType<CQmlViewEMS>("MyCustoms", 1, 0, "CQmlViewEMS");
	qmlRegisterType<CQmlViewGalwan>("MyCustoms", 1, 0, "CQmlViewGalwan");
	qmlRegisterType<CQmlViewVacuum>("MyCustoms", 1, 0, "CQmlViewVacuum");
	qmlRegisterType<CQmlViewProgramSelect>("MyCustoms", 1, 0, "CQmlViewProgramSelect");

}

void CQmlMainViewFrame::Initialize()
{
	CQmlMainView* pViewMain = this->rootObject()->findChild<CQmlMainView*>( rootObject()->objectName() + "_MainView" );
	qDebug()<<pViewMain;
	if ( pViewMain )
	{
		pViewMain->Initialize();
	}
//	keepScreenOn();

//	QAndr
}


// calls following java code:
// getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

void CQmlMainViewFrame::keepScreenOn()
{
	QAndroidJniObject activity = QtAndroid::androidActivity();
	if ( activity.isValid() )
	{
		QAndroidJniObject window = activity.callObjectMethod( "getWindow", "()Landroid/view/Window;" );

		if (window.isValid())
		{
			const int FLAG_KEEP_SCREEN_ON = 128;
			window.callObjectMethod("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
			qDebug()<<"Window is valid, setting keep screen on";
//			QAndroidActivityResultReceiver result
		}
	}
}

//public class BootUpReceiver extends BroadcastReceiver{

//        @Override
//        public void onReceive(Context context, Intent intent) {
//                Intent i = new Intent(context, MyActivity.class);
//                i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
//                context.startActivity(i);
//        }

//}

void CQmlMainViewFrame::clearScreenOnFlags()
{
	QAndroidJniObject activity = QtAndroid::androidActivity();
	if ( activity.isValid() )
	{
		QAndroidJniObject window = activity.callObjectMethod( "getWindow", "()Landroid/view/Window;" );

		if (window.isValid())
		{
			const int FLAG_KEEP_SCREEN_ON = 128;
			window.callObjectMethod("clearFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
			qDebug()<<"Window is valid, disabling keep screen on";
		}
	}
}
