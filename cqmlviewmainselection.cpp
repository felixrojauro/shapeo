#include "cqmlviewmainselection.h"

CQmlViewMainSelection::CQmlViewMainSelection(QQuickItem *parent)
	: CQmlViewBase(parent)
	, m_pButtonInfusion( 0 )
	, m_pButtonPeelJet( 0 )
	, m_pButtonQuit( 0 )
	, m_pButtonShapeo( 0 )
{
}

void CQmlViewMainSelection::Initialize()
{
	m_pButtonInfusion = findChild<CQmlTextButton*>( objectName() + "_ButtonInfusion" );
	m_pButtonPeelJet = findChild<CQmlTextButton*>( objectName() + "_ButtonPeelJet" );
	m_pButtonQuit = findChild<CQmlTextButton*>( objectName() + "_ButtonQuit" );
	m_pButtonShapeo = findChild<CQmlTextButton*>( objectName() + "_ButtonShapeo" );
	if ( m_pButtonInfusion )
	{
		m_pButtonInfusion->SetPressedColor( MyCommon::COLOR_BEIGE );
		m_pButtonInfusion->SetNormalColor( MyCommon::COLOR_SHIT_YELLOW );
		m_pButtonInfusion->SetButtonText( QObject::tr( "Infusion" ) );
		connect( m_pButtonInfusion, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonInfusion, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
	if ( m_pButtonPeelJet )
	{
		m_pButtonPeelJet->SetPressedColor( MyCommon::COLOR_VIOLET );
		m_pButtonPeelJet->SetNormalColor( MyCommon::COLOR_SHIT_VIOLET );
		m_pButtonPeelJet->SetButtonText( QObject::tr( "PeelJet" ) );
		connect( m_pButtonPeelJet, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonPeelJet, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
	if ( m_pButtonQuit )
	{
		m_pButtonQuit->SetPressedColor( MyCommon::COLOR_DARK_RED );
		m_pButtonQuit->SetNormalColor( MyCommon::COLOR_RED );
		m_pButtonQuit->SetButtonText( QObject::tr( "Wyjście" ) );
		connect( m_pButtonQuit, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonQuit, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
	if ( m_pButtonShapeo )
	{
		m_pButtonShapeo->SetPressedColor( MyCommon::COLOR_DARK_SELEDIN );
		m_pButtonShapeo->SetNormalColor( MyCommon::COLOR_SELEDIN );
		m_pButtonShapeo->SetButtonText( QObject::tr( "Zabiegi\ntlenowe" ) );
		connect( m_pButtonShapeo, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonShapeo, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
}

void CQmlViewMainSelection::slotClicked(CClickableObject* a_pClickedObject)
{
	if ( a_pClickedObject && a_pClickedObject->m_eType == CClickableObject::TYPE_BUTTON )
	{
		if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonInfusion )
		{
			ManageButtonInfusionClicked( 500, 500 );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonPeelJet )
		{
			ManageButtonPeelJetClicked( 500, 50 );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonQuit )
		{
			qApp->quit();
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonShapeo )
		{
			ManageButtonShapeoClicked( 50, 500 );
		}
	}
}

void CQmlViewMainSelection::slotClicked( CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY )
{
	if ( a_pClickedObject && a_pClickedObject->m_eType == CClickableObject::TYPE_BUTTON )
	{
		if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonInfusion )
		{
			ManageButtonInfusionClicked( a_fMouseX, a_fMouseY );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonPeelJet )
		{
			ManageButtonPeelJetClicked( a_fMouseX, a_fMouseY );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonQuit )
		{
			qApp->quit();
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonShapeo )
		{
			ManageButtonShapeoClicked( a_fMouseX, a_fMouseY );
		}
	}
}

void CQmlViewMainSelection::ManageButtonInfusionClicked( float a_fMouseX, float a_fMouseY )
{
//	slotSendMessage( "EMS" );
	emit signalShowInfusion( a_fMouseX, a_fMouseY );
}

void CQmlViewMainSelection::ManageButtonPeelJetClicked( float a_fMouseX, float a_fMouseY )
{
//	slotSendMessage( "GALWAN" );
	emit signalShowPeelJet( a_fMouseX, a_fMouseY );
}

void CQmlViewMainSelection::ManageButtonShapeoClicked( float a_fMouseX, float a_fMouseY )
{
	slotSendMessage( "OXYON" );
//	slotSendMessage( "VACONLY" );
	emit signalShowShapeo( a_fMouseX, a_fMouseY );
}
