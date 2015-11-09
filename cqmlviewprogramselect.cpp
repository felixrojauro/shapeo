#include "cqmlviewprogramselect.h"

CQmlViewProgramSelect::CQmlViewProgramSelect(QQuickItem *parent)
	: CQmlViewBase(parent)
	, m_pButtonEMS( 0 )
	, m_pButtonOxyTreatment( 0 )
	, m_pButtonBack( 0 )
	, m_pButtonInfusion( 0 )
{
}

void CQmlViewProgramSelect::Initialize()
{
	m_pButtonEMS = findChild<CQmlTextButton*>( objectName() + "_ButtonEMS" );
	m_pButtonInfusion = findChild<CQmlTextButton*>( objectName() + "_ButtonInfusion" );
	m_pButtonBack = findChild<CQmlTextButton*>( objectName() + "_ButtonQuit" );
	m_pButtonOxyTreatment = findChild<CQmlTextButton*>( objectName() + "_ButtonOxyTreatment" );
	if ( m_pButtonEMS )
	{
		m_pButtonEMS->SetPressedColor( MyCommon::COLOR_BEIGE );
		m_pButtonEMS->SetNormalColor( MyCommon::COLOR_LIGHT_BEIGE );
		m_pButtonEMS->SetButtonText( QObject::tr( "Oxy Massage" ) );
		connect( m_pButtonEMS, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonEMS, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
	if ( m_pButtonOxyTreatment )
	{
		m_pButtonOxyTreatment->SetPressedColor( MyCommon::COLOR_GREY );
		m_pButtonOxyTreatment->SetNormalColor( MyCommon::COLOR_LIGHT_GREY );
		m_pButtonOxyTreatment->SetButtonText( QObject::tr( "Natlenianie" ) );
		connect( m_pButtonOxyTreatment, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonOxyTreatment, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
	if ( m_pButtonBack )
	{
		m_pButtonBack->SetPressedColor( MyCommon::COLOR_DARK_RED );
		m_pButtonBack->SetNormalColor( MyCommon::COLOR_RED );
		m_pButtonBack->SetButtonText( QObject::tr( "Powrót" ) );
		connect( m_pButtonBack, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonBack, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
	if ( m_pButtonInfusion )
	{
		m_pButtonInfusion->SetPressedColor( MyCommon::COLOR_KHAKI );
		m_pButtonInfusion->SetNormalColor( MyCommon::COLOR_LIGHT_KHAKI );
		m_pButtonInfusion->SetButtonText( QObject::tr( "Infuzja" ) );
		connect( m_pButtonInfusion, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonInfusion, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
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
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonOxyTreatment )
		{
			ManageButtonOxyTreatmentClicked( 50, 500 );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonBack )
		{
			ManageButtonBackClicked( 700, 500 );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonInfusion )
		{
			ManageButtonInfusionClicked( 500, 50 );
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
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonOxyTreatment )
		{
			ManageButtonOxyTreatmentClicked( a_fMouseX, a_fMouseY );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonBack )
		{
			ManageButtonBackClicked( a_fMouseX, a_fMouseY );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonInfusion )
		{
			ManageButtonInfusionClicked( a_fMouseX, a_fMouseY );
		}
	}
}

void CQmlViewProgramSelect::ManageButtonEMSClicked( float a_fMouseX, float a_fMouseY )
{
	slotSendMessage( "EMS" );
	emit signalShowEMS( a_fMouseX, a_fMouseY );
}

void CQmlViewProgramSelect::ManageButtonInfusionClicked( float a_fMouseX, float a_fMouseY )
{
	slotSendMessage( "INFUSION" );
	emit signalShowInfusion( a_fMouseX, a_fMouseY );
}

void CQmlViewProgramSelect::ManageButtonOxyTreatmentClicked( float a_fMouseX, float a_fMouseY )
{
	slotSendMessage( "VACONLY" );
	emit signalShowOxyTreatment( a_fMouseX, a_fMouseY );
}

void CQmlViewProgramSelect::ManageButtonBackClicked( float a_fMouseX, float a_fMouseY )
{
	slotSendMessage( "OXYOFF" );
	emit signalBackToMainSelectionView( a_fMouseX, a_fMouseY );
}
