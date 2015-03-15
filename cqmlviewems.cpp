#include "cqmlviewems.h"

CQmlViewEMS::CQmlViewEMS(QQuickItem *parent)
	: CQmlViewBase(parent)
	, m_pButtonBack( 0 )
	, m_pButtonPlay( 0 )
	, m_pSliderAmplitute( 0 )
	, m_pSliderFrequency( 0 )
	, m_pSliderPulseWidth( 0 )
{
}

void CQmlViewEMS::Initialize()
{
	m_pButtonBack = findChild<CQmlTextButton*>( objectName() + "_ButtonBack" );
	m_pButtonPlay = findChild<CQmlTextButton*>( objectName() + "_ButtonPlay" );
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

	m_pSliderAmplitute = findChild<CQmlSlider*>( objectName() + "_SliderAmplitude" );
	m_pSliderFrequency = findChild<CQmlSlider*>( objectName() + "_SliderFrequency" );
	m_pSliderPulseWidth = findChild<CQmlSlider*>( objectName() + "_SliderPulseWidth" );
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
	if ( m_pSliderFrequency )
	{
		m_pSliderFrequency->SetColorBase( MyCommon::COLOR_RED );
		m_pSliderFrequency->SetColorBorder( MyCommon::COLOR_DARK_RED );
		m_pSliderFrequency->SetColorHandlePressed( MyCommon::COLOR_DARK_RED );
		m_pSliderFrequency->SetColorHandleReleased( MyCommon::COLOR_RED );

		m_pSliderFrequency->SetMaximumValue( 30 );
		m_pSliderFrequency->SetMinimumValue( 1 );
		m_pSliderFrequency->SetStepSize( 1 );
		m_pSliderFrequency->SetSliderName( QObject::tr( "Częstotliwość" ) );
		m_pSliderFrequency->SetValueSuffix( "Hz" );
		m_pSliderFrequency->SetValue( 15 );
		m_pSliderFrequency->SetValue( m_pSliderFrequency->GetMinimumValue() );

		connect( m_pSliderFrequency, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
	}
	if ( m_pSliderPulseWidth )
	{
		m_pSliderPulseWidth->SetColorBase( MyCommon::COLOR_VIOLET );
		m_pSliderPulseWidth->SetColorBorder( MyCommon::COLOR_DARK_VIOLET );
		m_pSliderPulseWidth->SetColorHandlePressed( MyCommon::COLOR_VIOLET );
		m_pSliderPulseWidth->SetColorHandleReleased( MyCommon::COLOR_LIGHT_VIOLET );

		m_pSliderPulseWidth->SetMaximumValue( 100 );
		m_pSliderPulseWidth->SetMinimumValue( 5 );
		m_pSliderPulseWidth->SetStepSize( 5 );
		m_pSliderPulseWidth->SetSliderName( QObject::tr( "Wypełnienie" ) );
		m_pSliderPulseWidth->SetValueSuffix( "%" );
		m_pSliderPulseWidth->SetValue( 50 );
		m_pSliderPulseWidth->SetValue( m_pSliderPulseWidth->GetMinimumValue() );

		connect( m_pSliderPulseWidth, SIGNAL(signalClicked(CClickableObject*)), this, SLOT( slotClicked(CClickableObject*)) );
	}

}

void CQmlViewEMS::slotClicked(CClickableObject* a_pClickedObject)
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
	if ( a_pClickedObject && a_pClickedObject->m_eType == CClickableObject::TYPE_SLIDER )
	{
		if ( static_cast<CQmlSlider*>( a_pClickedObject ) == m_pSliderAmplitute )
		{
			slotSendMessage( "CURRENT#" + QString::number( m_pSliderAmplitute->GetValue() ) );
		}
		else if ( static_cast<CQmlSlider*>( a_pClickedObject ) == m_pSliderFrequency )
		{
			slotSendMessage( "FREQ#" + QString::number( m_pSliderFrequency->GetValue() ) );
		}
		else if ( static_cast<CQmlSlider*>( a_pClickedObject ) == m_pSliderPulseWidth )
		{
			slotSendMessage( "FILLFACTOR#" + QString::number( m_pSliderPulseWidth->GetValue() ) );
		}
	}
}

void CQmlViewEMS::slotClicked(CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY)
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
	if ( a_pClickedObject && a_pClickedObject->m_eType == CClickableObject::TYPE_SLIDER )
	{
		if ( static_cast<CQmlSlider*>( a_pClickedObject ) == m_pSliderAmplitute )
		{
			slotSendMessage( "CURRENT#" + QString::number( m_pSliderAmplitute->GetValue() ) );
		}
		else if ( static_cast<CQmlSlider*>( a_pClickedObject ) == m_pSliderFrequency )
		{
			slotSendMessage( "FREQ#" + QString::number( m_pSliderFrequency->GetValue() ) );
		}
		else if ( static_cast<CQmlSlider*>( a_pClickedObject ) == m_pSliderPulseWidth )
		{
			slotSendMessage( "FILLFACTOR#" + QString::number( m_pSliderPulseWidth->GetValue() ) );
		}
	}
}

void CQmlViewEMS::ManagePlayButtonClicked( float /*a_fMouseX*/, float /*a_fMouseY*/ )
{
	if ( m_pButtonPlay && m_pButtonPlay->property( "state" ).toString() == "start" )
	{
		slotSendMessage( "EMS" );
		slotSendMessage( "CURRENT#" + QString::number( m_pSliderAmplitute->GetValue() ) );
		slotSendMessage( "FREQ#" + QString::number( m_pSliderFrequency->GetValue() ) );
		slotSendMessage( "FILLFACTOR#" + QString::number( m_pSliderPulseWidth->GetValue() ) );

		slotSendMessage( "START" );
		m_pButtonPlay->setProperty( "state", QVariant( "stop") );
	}
	else if ( m_pButtonPlay && m_pButtonPlay->property( "state" ).toString() == "stop" )
	{
		slotSendMessage( "STOP" );
		m_pButtonPlay->setProperty( "state", QVariant( "start") );
	}
}

void CQmlViewEMS::ManageBackButtonClicked( float a_fMouseX, float a_fMouseY )
{
	if ( m_pButtonPlay )
	{
		slotSendMessage( "STOP" );
		m_pButtonPlay->setProperty( "state", QVariant( "start") );
	}
	emit signalBackToProgramSelectView( a_fMouseX, a_fMouseY );
}
