#include "cqmlviewpeeljet.h"

CQmlViewPeelJet::CQmlViewPeelJet(QQuickItem *parent)
	: CQmlViewBase(parent)
	, m_pButtonBack( 0 )
	, m_pButtonPlay( 0 )
{
}

void CQmlViewPeelJet::Initialize()
{
	m_pButtonBack = findChild<CQmlTextButton*>( objectName() + "_ButtonBack" );
	m_pButtonPlay = findChild<CQmlTextButton*>( objectName() + "_ButtonPlay" );
	if ( m_pButtonBack )
	{
		connect( m_pButtonBack, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonBack, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
	if ( m_pButtonPlay )
	{
		connect( m_pButtonPlay, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonPlay, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)) );
	}
}

void CQmlViewPeelJet::slotClicked(CClickableObject* a_pClickedObject)
{
	if ( a_pClickedObject && a_pClickedObject->m_eType == CClickableObject::TYPE_BUTTON )
	{
		if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonPlay )
		{
			ManagePlayButtonClicked( 0, 0 );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonBack )
		{
			ManageBackButtonClicked( 0, 0 );
		}
	}
}

void CQmlViewPeelJet::slotClicked(CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY )
{
	if ( a_pClickedObject && a_pClickedObject->m_eType == CClickableObject::TYPE_BUTTON )
	{
		if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonPlay )
		{
			ManagePlayButtonClicked( a_fMouseX, a_fMouseY );
		}
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonBack )
		{
			ManageBackButtonClicked( a_fMouseX, a_fMouseY );
		}
	}
}

void CQmlViewPeelJet::ManagePlayButtonClicked(float /*a_fMouseX*/, float /*a_fMouseY*/ )
{
	if ( m_pButtonPlay && m_pButtonPlay->property( "state" ).toString() == "start" )
	{
		slotSendMessage( "PEELJET" );
		slotSendMessage( "START" );
		m_pButtonPlay->setProperty( "state", QVariant( "stop") );
	}
	else if ( m_pButtonPlay && m_pButtonPlay->property( "state" ).toString() == "stop" )
	{
		slotSendMessage( "PEELJET" );
		slotSendMessage( "STOP" );
		m_pButtonPlay->setProperty( "state", QVariant( "start") );
	}
}

void CQmlViewPeelJet::ManageBackButtonClicked( float a_fMouseX, float a_fMouseY )
{
	if ( m_pButtonPlay )
	{
		slotSendMessage( "PEELJET" );
		slotSendMessage( "STOP" );
		m_pButtonPlay->setProperty( "state", QVariant( "start") );
	}
	emit signalBackToMainSelectionView( a_fMouseX, a_fMouseY );
}
