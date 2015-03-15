#include "cqmlviewvacuum.h"

CQmlViewVacuum::CQmlViewVacuum(QQuickItem *parent)
	: CQmlViewBase(parent)
	, m_pButtonBack( 0 )
	, m_pButtonPlay( 0 )
{
}

void CQmlViewVacuum::Initialize()
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

void CQmlViewVacuum::slotClicked(CClickableObject* a_pClickedObject)
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

void CQmlViewVacuum::slotClicked(CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY )
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

void CQmlViewVacuum::ManagePlayButtonClicked(float /*a_fMouseX*/, float /*a_fMouseY*/ )
{
	if ( m_pButtonPlay && m_pButtonPlay->property( "state" ).toString() == "start" )
	{
		slotSendMessage( "VACONLY" );
		slotSendMessage( "START" );
		m_pButtonPlay->setProperty( "state", QVariant( "stop") );
	}
	else if ( m_pButtonPlay && m_pButtonPlay->property( "state" ).toString() == "stop" )
	{
		slotSendMessage( "VACONLY" );
		slotSendMessage( "STOP" );
		m_pButtonPlay->setProperty( "state", QVariant( "start") );
	}
}

void CQmlViewVacuum::ManageBackButtonClicked( float a_fMouseX, float a_fMouseY )
{
	if ( m_pButtonPlay )
	{
		slotSendMessage( "VACONLY" );
		slotSendMessage( "STOP" );
		m_pButtonPlay->setProperty( "state", QVariant( "start") );
	}
	emit signalBackToProgramSelectView( a_fMouseX, a_fMouseY );
}
