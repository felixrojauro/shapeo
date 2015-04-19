#include "cfullscreenpopupanimation.h"
#include "cqmlviewbase.h"
/////////////////////////////////////////////////////////////////////////////
/*!
//\par		Description:
//			Constructor.
//
//\par		Parameters:
//\arg		[IN] \b a_pParent			- pointer to parent object. Default is 0.
//
//\par		Return value:
//			None.
*/
CFullScreenPopupAnimation::CFullScreenPopupAnimation( QObject* a_pParent )
	: QObject( a_pParent )
	, m_fWidgetBasePositionX( 0 )
	, m_fWidgetBasePositionY( 0 )
	, m_pTargetWidget( 0 )
	, m_pRepositionXAnimation( new QPropertyAnimation )
	, m_pRepositionYAnimation( new QPropertyAnimation )
	, m_pScaleAnimation( new QPropertyAnimation )
	, m_pWidgetAnimation( new QParallelAnimationGroup )
	, m_bShow( false )
{
	if ( m_pRepositionXAnimation && m_pRepositionYAnimation && m_pScaleAnimation && m_pWidgetAnimation )
	{
		m_pWidgetAnimation->addAnimation( m_pRepositionXAnimation );
		m_pWidgetAnimation->addAnimation( m_pRepositionYAnimation );
		m_pWidgetAnimation->addAnimation( m_pScaleAnimation );
	}
}

/////////////////////////////////////////////////////////////////////////////
/*!
//\par		Description:
//			Destructor.
//
//\par		Parameters:
//\arg		None.
//
//\par		Return value:
//			None.
*/
CFullScreenPopupAnimation::~CFullScreenPopupAnimation()
{
	// The group takes ownership of the animation, so the will be deleted when group is deleted.
	if ( m_pWidgetAnimation )
	{
		delete m_pWidgetAnimation;
		m_pWidgetAnimation = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////
/*!
//\par		Description:
//			Prepares animations for current setup.
//
//\par		Parameters:
//			None.
//
//\par		Return value:
//			true if succeeded, false otherwise
*/
bool CFullScreenPopupAnimation::PrepareAnimation()
{
	if ( m_pRepositionXAnimation && m_pRepositionYAnimation && m_pScaleAnimation )
	{
		m_pRepositionXAnimation->setPropertyName( "x" );
		m_pRepositionYAnimation->setPropertyName( "y" );
		m_pScaleAnimation->setPropertyName( "scale" );

		connect( m_pWidgetAnimation, SIGNAL( finished() ), this, SLOT( slotAnimationFinished() ), Qt::UniqueConnection );
		return true;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////
/*!
//\par		Description:
//			Starts popup show/hide animation
//
//\par		Parameters:
//\arg		[IN] \b a_bShow		- if true - show, otherwise hide
//\arg		[IN] \b a_iDuration	- animation duration in [ms]
//
//\par		Return value:
//			true if succeeded, false otherwise
*/
bool CFullScreenPopupAnimation::StartAnimation( bool a_bShow, int a_iDuration )
{
	if ( a_bShow == m_pTargetWidget->isVisible() && m_bShow == a_bShow )
	{
		qDebug()<<"m_pTargetWidget: "<<m_pTargetWidget->objectName()<<" my Z: "<<m_pTargetWidget->z()<<" already good";
		return true;
	}
	if ( m_pRepositionXAnimation && m_pRepositionYAnimation && m_pScaleAnimation && m_pWidgetAnimation )
	{
		if ( m_pWidgetAnimation->state() != QAbstractAnimation::Stopped )
		{
			m_pWidgetAnimation->stop();
		}

		m_pRepositionXAnimation->setDuration( a_iDuration );
		m_pRepositionYAnimation->setDuration( a_iDuration );
		m_pScaleAnimation->setDuration( a_iDuration );

		m_pRepositionXAnimation->setTargetObject( m_pTargetWidget );
		m_pRepositionYAnimation->setTargetObject( m_pTargetWidget );
		m_pScaleAnimation->setTargetObject( m_pTargetWidget );

		if ( a_bShow )
		{
//			m_pTargetWidget->setZ( m_pTargetWidget->z() + 5 );
			m_pTargetWidget->setVisible( true );
			m_pTargetWidget->setEnabled( true );
			m_pRepositionXAnimation->setStartValue( m_fWidgetBasePositionX );
			m_pRepositionXAnimation->setEndValue( 0 );

			m_pRepositionYAnimation->setStartValue( m_fWidgetBasePositionY );
			m_pRepositionYAnimation->setEndValue( 0 );

			m_pScaleAnimation->setStartValue( m_pTargetWidget->scale() );
			m_pScaleAnimation->setEndValue( 1 );
		}
		else
		{
			m_pRepositionXAnimation->setStartValue( 0 );
			m_pRepositionXAnimation->setEndValue( m_fWidgetBasePositionX );

			m_pRepositionYAnimation->setStartValue( 0 );
			m_pRepositionYAnimation->setEndValue( m_fWidgetBasePositionY );

			m_pScaleAnimation->setStartValue( m_pTargetWidget->scale() );
			m_pScaleAnimation->setEndValue( 0 );
		}

		m_bShow = a_bShow;
		m_pWidgetAnimation->start();
		return true;
	}

	return false;
}

void CFullScreenPopupAnimation::slotAnimationFinished()
{
	if ( !m_bShow )
	{
//		m_pTargetWidget->setZ( m_pTargetWidget->z() - 5 );
		m_pTargetWidget->setVisible( false );
		m_pTargetWidget->setEnabled( false );
	}
	emit signalAnimationFinished( m_pTargetWidget, m_bShow );
}
