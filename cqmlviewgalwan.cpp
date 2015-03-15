#include "cqmlviewgalwan.h"

CQmlViewGalwan::CQmlViewGalwan(QQuickItem *parent)
	: CQmlViewBase(parent)
	, m_pButtonBack( 0 )
	, m_pButtonPlay( 0 )
	, m_pButtonPlayVacuum( 0 )
	, m_pSliderAmplitute( 0 )
{
}

void CQmlViewGalwan::Initialize()
{
	m_pButtonBack			= findChild<CQmlTextButton*>( objectName() + "_ButtonBack" );
	m_pButtonPlay			= findChild<CQmlTextButton*>( objectName() + "_ButtonPlay" );
	m_pButtonPlayVacuum		= findChild<CQmlTextButton*>( objectName() + "_ButtonPlayVacuum" );
	m_pSliderAmplitute		= findChild<CQmlSlider*>( objectName() + "_SliderAmplitude" );
	if ( m_pButtonBack )
	{
		connect( m_pButtonBack, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonBack, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)), Qt::UniqueConnection );
	}
	if ( m_pButtonPlay )
	{
		connect( m_pButtonPlay, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonPlay, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)), Qt::UniqueConnection );
	}
	if ( m_pButtonPlayVacuum )
	{
		connect( m_pButtonPlayVacuum, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
		connect( m_pButtonPlayVacuum, SIGNAL(signalClicked(CClickableObject*,float,float)), this, SLOT( slotClicked(CClickableObject*,float,float)), Qt::UniqueConnection );
	}
	if ( m_pSliderAmplitute )
	{
		m_pSliderAmplitute->SetColorBase( MyCommon::COLOR_GREEN );
		m_pSliderAmplitute->SetColorBorder( MyCommon::COLOR_DARK_GREEN );
		m_pSliderAmplitute->SetColorHandlePressed( MyCommon::COLOR_DARK_GREEN );
		m_pSliderAmplitute->SetColorHandleReleased( MyCommon::COLOR_GREEN );

		m_pSliderAmplitute->SetMaximumValue( 30 );
		m_pSliderAmplitute->SetMinimumValue( 1 );
		m_pSliderAmplitute->SetStepSize( 1 );
		m_pSliderAmplitute->SetSliderName( QObject::tr( "Amplituda" ) );
		m_pSliderAmplitute->SetValueSuffix( "V" );
		m_pSliderAmplitute->SetValue( 15 );
		m_pSliderAmplitute->SetValue( m_pSliderAmplitute->GetMinimumValue() );

		connect( m_pSliderAmplitute, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
	}

}

void CQmlViewGalwan::slotClicked(CClickableObject* a_pClickedObject)
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
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonPlayVacuum )
		{
			ManagePlayVacuumButtonClicked( 0, 0 );
		}
	}
	if ( a_pClickedObject && a_pClickedObject->m_eType == CClickableObject::TYPE_SLIDER )
	{
		if ( static_cast<CQmlSlider*>( a_pClickedObject ) == m_pSliderAmplitute )
		{
			slotSendMessage( "CURRENT#" + QString::number( m_pSliderAmplitute->GetValue() ) );
		}

	}
}

void CQmlViewGalwan::slotClicked(CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY )
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
		else if ( static_cast<CQmlTextButton*>( a_pClickedObject ) == m_pButtonPlayVacuum )
		{
			ManagePlayVacuumButtonClicked( a_fMouseX, a_fMouseY );
		}
	}
	if ( a_pClickedObject && a_pClickedObject->m_eType == CClickableObject::TYPE_SLIDER )
	{
		if ( static_cast<CQmlSlider*>( a_pClickedObject ) == m_pSliderAmplitute )
		{
			slotSendMessage( "CURRENT#" + QString::number( m_pSliderAmplitute->GetValue() ) );
		}

	}
}

void CQmlViewGalwan::ManagePlayButtonClicked( float /*a_fMouseX*/, float /*a_fMouseY*/ )
{
	if ( m_pButtonPlay && m_pButtonPlay->property( "state" ).toString() == "start" )
	{
		slotSendMessage( "GALWAN" );
		slotSendMessage( "CURRENT#" + QString::number( m_pSliderAmplitute->GetValue() ) );
		slotSendMessage( "START" );
		m_pButtonPlay->setProperty( "state", QVariant( "stop") );
		// if vacuum is set to default ( start ) then start vacuum automatically
		if ( m_pButtonPlayVacuum && m_pButtonPlayVacuum->property( "state" ).toString() == "start" )
		{
			slotSendMessage( "VACUUMON" );
			m_pButtonPlayVacuum->setProperty( "state", QVariant( "stop") );
		}
	}
	else if ( m_pButtonPlay && m_pButtonPlay->property( "state" ).toString() == "stop" )
	{
		slotSendMessage( "GALWAN" );
		slotSendMessage( "STOP" );
		m_pButtonPlay->setProperty( "state", QVariant( "start") );
		// when galwan stopped, stop vacuum as well
		if ( m_pButtonPlayVacuum )
		{
			slotSendMessage( "VACUUMOFF" );
			m_pButtonPlayVacuum->setProperty( "state", QVariant( "start") );
		}
	}
}

void CQmlViewGalwan::ManageBackButtonClicked( float a_fMouseX, float a_fMouseY )
{
	if ( m_pButtonPlay )
	{
		slotSendMessage( "GALWAN" );
		slotSendMessage( "STOP" );
		m_pButtonPlay->setProperty( "state", QVariant( "start") );
	}
	if ( m_pButtonPlayVacuum )
	{
		slotSendMessage( "GALWAN" );
		slotSendMessage( "VACUUMOFF" );
		m_pButtonPlayVacuum->setProperty( "state", QVariant( "start") );
	}
	emit signalBackToProgramSelectView( a_fMouseX, a_fMouseY );
}

void CQmlViewGalwan::ManagePlayVacuumButtonClicked( float /*a_fMouseX*/, float /*a_fMouseY*/ )
{
	if ( m_pButtonPlayVacuum && m_pButtonPlayVacuum->property( "state" ).toString() == "start" )
	{
		slotSendMessage( "START" );
		m_pButtonPlayVacuum->setProperty( "state", QVariant( "stop") );
	}
	else if ( m_pButtonPlayVacuum && m_pButtonPlayVacuum->property( "state" ).toString() == "stop" )
	{
		slotSendMessage( "VACUUMOFF" );
		m_pButtonPlayVacuum->setProperty( "state", QVariant( "start") );
	}
}
