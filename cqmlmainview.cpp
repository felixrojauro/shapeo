#include "cqmlmainview.h"

#include "cqmlviewbase.h"

#include <QTime>

CQmlMainView::CQmlMainView(QQuickItem *parent)
	: QQuickItem(parent)
	, m_pBTThread( new QThread )
	, m_pBTConnector( new CAndroidRFCOMMConnector() )
	, m_pViewEMS( 0 )
	, m_pViewGalwan( 0 )
	, m_pViewProgramSelect( 0 )
	, m_pViewVacuum( 0 )
	, m_pViewMainSelection( 0 )
	, m_pViewInfusion( 0 )
	, m_pViewPeelJet( 0 )
	, m_strAppState( "unknown" )
	, m_bBTLifemarkOK( false )
	, m_bBTConnected( false )
	, m_bBTDuringConnection( false )
{
	timerLifemark.setSingleShot( false );
	timerLifemark.setInterval( 1000 );
	connect( &timerLifemark, SIGNAL( timeout() ), this, SLOT( slotSendLifemarkRequest() ) );

	timerLifemarkSupressor.setSingleShot( false );
	timerLifemarkSupressor.setInterval( 1000 );
	connect( &timerLifemarkSupressor, SIGNAL( timeout() ), &timerLifemark, SLOT( start() ) );
	connect( &timerLifemarkSupressor, SIGNAL( timeout() ), &timerLifemarkSupressor, SLOT( stop() ) );

	if ( m_pBTConnector && m_pBTThread )
	{
		m_pBTConnector->moveToThread( m_pBTThread );
		connect( this, SIGNAL( signalBTConnect() ), m_pBTConnector, SLOT( slotConnect() ), Qt::QueuedConnection);
		connect( this, SIGNAL( signalBTDisconnect() ), m_pBTConnector, SLOT( slotDisconnect() ), Qt::QueuedConnection );
		connect( this, SIGNAL( signalSendMessage(QString)), m_pBTConnector, SLOT( slotSendMessage(QString)), Qt::QueuedConnection );
		connect( m_pBTThread, SIGNAL( started()), m_pBTConnector, SLOT( slotProcess() ), Qt::QueuedConnection);
		connect( m_pBTConnector, SIGNAL( signalFinished() ), m_pBTConnector, SLOT( deleteLater() ), Qt::QueuedConnection);
		connect( m_pBTConnector, SIGNAL( signalDuringConnection( bool )), this, SLOT( slotBTDuringConnection(bool) ) );
		connect( m_pBTConnector, SIGNAL( signalReceivedMessage(QString) ), this, SLOT( slotUpdateLifemark(QString) ) );
		connect( m_pBTConnector, SIGNAL( signalConnectFinished(bool)), this, SLOT( slotBTConnectFinished(bool)) );
		connect( m_pBTConnector, SIGNAL( signalFinished() ), m_pBTThread, SLOT( quit() ) );
		connect( m_pBTConnector, SIGNAL( signalFinished() ), m_pBTThread, SLOT( deleteLater() ) );
		m_pBTThread->start();
	}
}

void CQmlMainView::Initialize()
{
	// initialize connection

	emit signalBTConnect();

	// initialize views
	m_pViewEMS				= findChild<CQmlViewEMS*>( objectName() + "_ViewEMS" );
	m_pViewGalwan			= findChild<CQmlViewGalwan*>( objectName() + "_ViewGalwan" );
	m_pViewProgramSelect	= findChild<CQmlViewProgramSelect*>( objectName() + "_ViewProgramSelect" );
	m_pViewVacuum			= findChild<CQmlViewVacuum*>( objectName() + "_ViewVacuum" );

	m_pViewMainSelection	= findChild<CQmlViewMainSelection*>( objectName() + "_ViewMainSelection" );
	m_pViewInfusion			= findChild<CQmlViewInfusion*>( objectName() + "_ViewInfusion" );
	m_pViewPeelJet			= findChild<CQmlViewPeelJet*>( objectName() + "_ViewPeelJet" );
	if ( m_pViewEMS )
	{
		m_pViewEMS->Initialize();
		connect( m_pViewEMS, SIGNAL( signalBackToProgramSelectView(float,float)), this, SLOT( slotShowViewProgramSelect(float,float)) );
		connect( m_pViewEMS, SIGNAL( signalSendMessage(QString)), this, SLOT( slotCatchSendRequests(QString)) );
	}
	if ( m_pViewGalwan )
	{
		m_pViewGalwan->Initialize();
		connect( m_pViewGalwan, SIGNAL( signalBackToProgramSelectView(float,float)), this, SLOT( slotShowViewProgramSelect(float,float)) );
		connect( m_pViewGalwan, SIGNAL( signalSendMessage(QString)), this, SLOT( slotCatchSendRequests(QString)) );
	}
	if ( m_pViewProgramSelect )
	{
		m_pViewProgramSelect->Initialize();
		connect( m_pViewProgramSelect, SIGNAL( signalShowEMS(float,float)), this, SLOT(slotShowViewEMS(float,float)));
		connect( m_pViewProgramSelect, SIGNAL( signalShowGalwan(float,float)), this, SLOT(slotShowViewGalwan(float,float)));
		connect( m_pViewProgramSelect, SIGNAL( signalShowVacuum(float,float)), this, SLOT(slotShowViewVacuum(float,float)));
		connect( m_pViewProgramSelect, SIGNAL( signalSendMessage(QString)), this, SLOT( slotCatchSendRequests(QString)) );
		connect( m_pViewProgramSelect, SIGNAL( signalBackToMainSelectionView(float,float)), this, SLOT( slotShowViewMainSelection(float,float)) );
	}
	if ( m_pViewVacuum )
	{
		m_pViewVacuum->Initialize();
		connect( m_pViewVacuum, SIGNAL( signalBackToProgramSelectView(float,float)), this, SLOT( slotShowViewProgramSelect(float,float)) );
		connect( m_pViewVacuum, SIGNAL( signalSendMessage(QString)), this, SLOT( slotCatchSendRequests(QString)) );
	}

	if ( m_pViewMainSelection )
	{
		m_pViewMainSelection->Initialize();
		connect( m_pViewMainSelection, SIGNAL( signalShowInfusion(float,float)), this, SLOT(slotShowViewInfusion(float,float)));
		connect( m_pViewMainSelection, SIGNAL( signalShowPeelJet(float,float)), this, SLOT(slotShowViewPeelJet(float,float)));
		connect( m_pViewMainSelection, SIGNAL( signalShowShapeo(float,float)), this, SLOT(slotShowViewProgramSelect(float,float)));
		connect( m_pViewMainSelection, SIGNAL( signalSendMessage(QString)), this, SLOT( slotCatchSendRequests(QString)) );
	}
	if ( m_pViewInfusion )
	{
		m_pViewInfusion->Initialize();
		connect( m_pViewInfusion, SIGNAL( signalBackToMainSelectionView(float,float)), this, SLOT( slotShowViewMainSelection(float,float)) );
		connect( m_pViewInfusion, SIGNAL( signalSendMessage(QString)), this, SLOT( slotCatchSendRequests(QString)) );
	}
	if ( m_pViewPeelJet )
	{
		m_pViewPeelJet->Initialize();
		connect( m_pViewPeelJet, SIGNAL( signalBackToMainSelectionView(float,float)), this, SLOT( slotShowViewMainSelection(float,float)) );
		connect( m_pViewPeelJet, SIGNAL( signalSendMessage(QString)), this, SLOT( slotCatchSendRequests(QString)) );
	}

	m_pViewMainSelection->ShowAnimation( MyCommon::SCREEN_WIDTH / 2, MyCommon::SCREEN_HEIGHT / 2, 500 );

	m_pViewEMS->HideAnimation( 0, 0, 5 );
	m_pViewVacuum->HideAnimation(0, 0, 5 );
	m_pViewGalwan->HideAnimation(0, 0, 5 );
	m_pViewProgramSelect->HideAnimation( 0, 0, 5 );
	m_pViewEMS->setZ( 3 );
	m_pViewVacuum->setZ( 3 );
	m_pViewGalwan->setZ( 3 );
	m_pViewProgramSelect->setZ( 2 );

	m_pViewInfusion->HideAnimation(0, 0, 5 );
	m_pViewPeelJet->HideAnimation(0, 0, 5 );

}

QString CQmlMainView::GetAppState() const
{
	return m_strAppState;
}

void CQmlMainView::SetAppState( QString a_strNewState )
{
	if ( m_strAppState != a_strNewState )
	{
		m_strAppState = a_strNewState;
//		if ( m_strAppState.contains( "no_connection" ) )
//		{
//			m_bBTConnected = false;
//			emit signalBTDisconnect();
//		}
		emit signalAppStateChanged();
	}
}

void CQmlMainView::slotShowViewEMS( float a_fMouseX, float a_fMouseY )
{
	if ( m_pViewMainSelection && m_pViewEMS && m_pViewGalwan && m_pViewProgramSelect && m_pViewVacuum && m_pViewInfusion && m_pViewPeelJet )
	{
//		m_pViewProgramSelect->HideAnimation( a_fMouseX, a_fMouseY );
//		m_pViewInfusion->HideAnimation( a_fMouseX, a_fMouseY );
//		m_pViewPeelJet->HideAnimation( a_fMouseX, a_fMouseY );

		m_pViewEMS->ShowAnimation( a_fMouseX, a_fMouseY );
		m_pViewVacuum->HideAnimation( a_fMouseX, a_fMouseY );
		m_pViewGalwan->HideAnimation( a_fMouseX, a_fMouseY );
	}
}

void CQmlMainView::slotShowViewGalwan( float a_fMouseX, float a_fMouseY )
{
	if ( m_pViewMainSelection && m_pViewEMS && m_pViewGalwan && m_pViewProgramSelect && m_pViewVacuum && m_pViewInfusion && m_pViewPeelJet )
	{
//		m_pViewProgramSelect->HideAnimation( a_fMouseX, a_fMouseY );
//		m_pViewInfusion->HideAnimation( a_fMouseX, a_fMouseY );
//		m_pViewPeelJet->HideAnimation( a_fMouseX, a_fMouseY );

		m_pViewEMS->HideAnimation( a_fMouseX, a_fMouseY );
		m_pViewVacuum->HideAnimation( a_fMouseX, a_fMouseY );
		m_pViewGalwan->ShowAnimation( a_fMouseX, a_fMouseY );
	}
}

void CQmlMainView::slotShowViewVacuum( float a_fMouseX, float a_fMouseY )
{
	if ( m_pViewMainSelection && m_pViewEMS && m_pViewGalwan && m_pViewProgramSelect && m_pViewVacuum && m_pViewInfusion && m_pViewPeelJet )
	{
//		m_pViewProgramSelect->HideAnimation( a_fMouseX, a_fMouseY );
//		m_pViewInfusion->HideAnimation( a_fMouseX, a_fMouseY );
//		m_pViewPeelJet->HideAnimation( a_fMouseX, a_fMouseY );

		m_pViewEMS->HideAnimation( a_fMouseX, a_fMouseY );
		m_pViewVacuum->ShowAnimation( a_fMouseX, a_fMouseY );
		m_pViewGalwan->HideAnimation( a_fMouseX, a_fMouseY );
	}
}

void CQmlMainView::slotShowViewProgramSelect( float a_fMouseX, float a_fMouseY )
{
	if ( m_pViewMainSelection && m_pViewEMS && m_pViewGalwan && m_pViewProgramSelect && m_pViewVacuum && m_pViewInfusion && m_pViewPeelJet )
	{
		m_pViewProgramSelect->ShowAnimation( a_fMouseX, a_fMouseY );
//		m_pViewInfusion->HideAnimation( a_fMouseX, a_fMouseY );
//		m_pViewPeelJet->HideAnimation( a_fMouseX, a_fMouseY );

		m_pViewEMS->HideAnimation( a_fMouseX, a_fMouseY );
		m_pViewVacuum->HideAnimation( a_fMouseX, a_fMouseY );
		m_pViewGalwan->HideAnimation( a_fMouseX, a_fMouseY );
	}
}

void CQmlMainView::slotShowViewMainSelection( float a_fMouseX, float a_fMouseY )
{
	if ( m_pViewMainSelection && m_pViewEMS && m_pViewGalwan && m_pViewProgramSelect && m_pViewVacuum && m_pViewInfusion && m_pViewPeelJet )
	{
//		m_pViewMainSelection->ShowAnimation( a_fMouseX, a_fMouseY );
		m_pViewProgramSelect->HideAnimation( a_fMouseX, a_fMouseY );
		m_pViewInfusion->HideAnimation( a_fMouseX, a_fMouseY );
		m_pViewPeelJet->HideAnimation( a_fMouseX, a_fMouseY );

//		m_pViewEMS->HideAnimation( a_fMouseX, a_fMouseY );
//		m_pViewVacuum->HideAnimation( a_fMouseX, a_fMouseY );
//		m_pViewGalwan->HideAnimation( a_fMouseX, a_fMouseY );
	}
}

void CQmlMainView::slotShowViewInfusion( float a_fMouseX, float a_fMouseY )
{
	m_pViewProgramSelect->HideAnimation( a_fMouseX, a_fMouseY );
	m_pViewInfusion->ShowAnimation( a_fMouseX, a_fMouseY );
	m_pViewPeelJet->HideAnimation( a_fMouseX, a_fMouseY );

//	m_pViewEMS->HideAnimation( a_fMouseX, a_fMouseY );
//	m_pViewVacuum->HideAnimation( a_fMouseX, a_fMouseY );
//	m_pViewGalwan->HideAnimation( a_fMouseX, a_fMouseY );
}

void CQmlMainView::slotShowViewPeelJet( float a_fMouseX, float a_fMouseY )
{
	m_pViewProgramSelect->HideAnimation( a_fMouseX, a_fMouseY );
	m_pViewInfusion->HideAnimation( a_fMouseX, a_fMouseY );
	m_pViewPeelJet->ShowAnimation( a_fMouseX, a_fMouseY );

//	m_pViewEMS->HideAnimation( a_fMouseX, a_fMouseY );
//	m_pViewVacuum->HideAnimation( a_fMouseX, a_fMouseY );
//	m_pViewGalwan->HideAnimation( a_fMouseX, a_fMouseY );
}

void CQmlMainView::slotUpdateLifemark( QString a_strDeviceAnswer )
{
//	if ( a_strDeviceAnswer.contains( CAndroidRFCOMMConnector::DEVICE_ANSWER_PREFIX + "#LIFEMARK" ) )
//	{
		m_bBTLifemarkOK = true;
//	}
}

void CQmlMainView::slotValidateLifemark()
{
//	if ( m_bBTLifemarkOK )
//	{
		SetAppState( "connection_ok" );
//	}
//	else
//	{
//		SetAppState( "no_connection" );
//		timerLifemark.stop();
//		if ( !m_bBTDuringConnection )
//			emit signalBTConnect();
//		if ( m_bBTConnected )
//		{
//			timerLifemark.start();
//		}
//		else
//		{
//			QTimer::singleShot( 1500, this, SLOT( slotValidateLifemark() ) );
//		}
//	}
}

void CQmlMainView::slotSendLifemarkRequest()
{
	if ( m_bBTConnected )
	{
		m_bBTLifemarkOK = false;
//		emit signalSendMessage( "LIFEMARK#" );
		QTimer::singleShot( 500, this, SLOT( slotValidateLifemark() ) );
	}
}

void CQmlMainView::slotCatchSendRequests(QString a_strMessageToSend)
{
	timerLifemark.stop();
	timerLifemarkSupressor.start();
	emit signalSendMessage( a_strMessageToSend );

}

void CQmlMainView::slotAnimationFinished(CQmlViewBase* /*a_pView*/, bool /*a_bShow*/)
{

}

void CQmlMainView::slotBTConnectFinished(bool a_bIsConnected)
{
	m_bBTConnected = a_bIsConnected;
//	if ( m_bBTConnected )
//	{
//		timerLifemark.start();
//	}
}

void CQmlMainView::slotBTDuringConnection(bool a_bIsDuringConnection)
{
	m_bBTDuringConnection = a_bIsDuringConnection;
}

