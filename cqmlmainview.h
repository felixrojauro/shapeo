#ifndef CQMLMAINVIEW_H
#define CQMLMAINVIEW_H

#include <QQuickItem>
#include <QTimer>
#include <QThread>

#include "cqmlviewems.h"
#include "cqmlviewgalwan.h"
#include "cqmlviewprogramselect.h"
#include "cqmlviewvacuum.h"
#include "cfullscreenpopupanimation.h"

#include "android_bt/candroidrfcommconnector.h"

class CQmlMainView : public QQuickItem
{
    Q_OBJECT

	Q_PROPERTY( QString m_strAppState READ GetAppState WRITE SetAppState NOTIFY signalAppStateChanged )
public:
    explicit CQmlMainView(QQuickItem *parent = 0);
	void Initialize();

	QString GetAppState() const;
	void SetAppState( QString a_strNewState );

public slots:
	void slotShowViewEMS( float a_fMouseX, float a_fMouseY );
	void slotShowViewGalwan( float a_fMouseX, float a_fMouseY );
	void slotShowViewVacuum( float a_fMouseX, float a_fMouseY );
	void slotShowViewProgramSelect( float a_fMouseX, float a_fMouseY );

	void slotUpdateLifemark( QString a_strDeviceAnswer );
	void slotValidateLifemark();
	void slotSendLifemarkRequest();

	void slotCatchSendRequests( QString a_strMessageToSend );

	void slotAnimationFinished( CQmlViewBase* a_pView, bool a_bShow );

	// BT
	void slotBTConnectFinished( bool a_bIsConnected );
	void slotBTDuringConnection( bool a_bIsDuringConnection );

signals:
	void signalAppStateChanged();
	void signalBTConnect();
	void signalBTDisconnect();
	void signalSendMessage( QString a_strMessage );

private:
	static const QString BT_DEVICE_NAME;

	QThread*					m_pBTThread;
	CAndroidRFCOMMConnector*	m_pBTConnector;

	CQmlViewEMS*			m_pViewEMS;
	CQmlViewGalwan*			m_pViewGalwan;
	CQmlViewProgramSelect*	m_pViewProgramSelect;
	CQmlViewVacuum*			m_pViewVacuum;

	QString m_strAppState;
	bool m_bBTLifemarkOK;
	QTimer timerLifemark;
	QTimer timerLifemarkSupressor;

	bool m_bBTConnected;
	bool m_bBTDuringConnection;
};

#endif // CQMLMAINVIEW_H
