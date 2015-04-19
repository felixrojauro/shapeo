#include "cqmlviewprogramselect.h"

CQmlViewProgramSelect::CQmlViewProgramSelect(QQuickItem *parent)
	: CQmlViewBase(parent)
	, m_pButtonEMS( 0 )
	, m_pButtonGalwan( 0 )
	, m_pButtonBack( 0 )
	, m_pButtonVacuum( 0 )
{
}

void CQmlViewProgramSelect::Initialize()
{
	m_pButtonEMS = findChild<CQmlTextButton*>( objectName() + "_ButtonEMS" );
	m_pButtonGalwan = findChild<CQmlTextButton*>( objectName() + "_Galwan" );
	m_pButtonBack = findChild<CQmlTextButton*>( objectName() + "_ButtonQuit" );
	m_pButtonVacuum = findChild<CQmlTextButton*>( objectName() + "_ButtonVacuum" );
	if ( m_pButtonEMS )
	{
		m_pButtonEMS->SetPressedColor( MyCommon::COLOR_BEIGE );
		m_pButtonEMS->SetNormalColor( MyCommon::COLOR_LIGHT_BEIGE );
		m_pButtonEMS->SetButtonText( QObject::tr( "EMS" ) );
		connect( m_pButtonEMS, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonEMS, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
	if ( m_pButtonGalwan )
	{
		m_pButtonGalwan->SetPressedColor( MyCommon::COLOR_GREY );
		m_pButtonGalwan->SetNormalColor( MyCommon::COLOR_LIGHT_GREY );
		m_pButtonGalwan->SetButtonText( QObject::tr( "Galwan" ) );
		connect( m_pButtonGalwan, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonGalwan, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
	if ( m_pButtonBack )
	{
		m_pButtonBack->SetPressedColor( MyCommon::COLOR_DARK_RED );
		m_pButtonBack->SetNormalColor( MyCommon::COLOR_RED );
		m_pButtonBack->SetButtonText( QObject::tr( "Powrót" ) );
		connect( m_pButtonBack, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonBack, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
	if ( m_pButtonVacuum )
	{
		m_pButtonVacuum->SetPressedColor( MyCommon::COLOR_KHAKI );
		m_pButtonVacuum->SetNormalColor( MyCommon::COLOR_LIGHT_KHAKI );
		m_pButtonVacuum->SetButtonText( QObject::tr( "Vacuum" ) );
		connect( m_pButtonVacuum, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonVacuum, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
}

void CQmlViewProgramSelect::slotClicked(CClickableObject* a_pClickedObject)
{
	if ( a_pClickedObject && a_pClickedObject->m_eType == CClickableObject::TYPE_BUTTON )
	{
		if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonEMS )
		{
			ManageButtonEMSClicked( 500, 500 );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonGalwan )
		{
			ManageButtonGalwanClicked( 500, 50 );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonBack )
		{
			ManageButtonBackClicked( 700, 500 );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonVacuum )
		{
			ManageButtonVacuumClicked( 50, 500 );
		}
	}
}

void CQmlViewProgramSelect::slotClicked( CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY )
{
	if ( a_pClickedObject && a_pClickedObject->m_eType == CClickableObject::TYPE_BUTTON )
	{
		if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonEMS )
		{
			ManageButtonEMSClicked( a_fMouseX, a_fMouseY );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonGalwan )
		{
			ManageButtonGalwanClicked( a_fMouseX, a_fMouseY );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonBack )
		{
			ManageButtonBackClicked( a_fMouseX, a_fMouseY );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonVacuum )
		{
			ManageButtonVacuumClicked( a_fMouseX, a_fMouseY );
		}
	}
}

void CQmlViewProgramSelect::ManageButtonEMSClicked( float a_fMouseX, float a_fMouseY )
{
	slotSendMessage( "EMS" );
	emit signalShowEMS( a_fMouseX, a_fMouseY );
}

void CQmlViewProgramSelect::ManageButtonGalwanClicked( float a_fMouseX, float a_fMouseY )
{
	slotSendMessage( "GALWAN" );
	emit signalShowGalwan( a_fMouseX, a_fMouseY );
}

void CQmlViewProgramSelect::ManageButtonVacuumClicked( float a_fMouseX, float a_fMouseY )
{
	slotSendMessage( "VACONLY" );
	emit signalShowVacuum( a_fMouseX, a_fMouseY );
}

void CQmlViewProgramSelect::ManageButtonBackClicked( float a_fMouseX, float a_fMouseY )
{
	emit signalBackToMainSelectionView( a_fMouseX, a_fMouseY );
}
