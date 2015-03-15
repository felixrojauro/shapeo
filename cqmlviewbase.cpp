#include "cqmlviewbase.h"

CQmlViewBase::CQmlViewBase(QQuickItem *parent) :
	QQuickItem(parent)
	, m_pPopupAnimation( new CFullScreenPopupAnimation( this ) )
{
	if ( m_pPopupAnimation )
	{
		m_pPopupAnimation->PrepareAnimation();
		m_pPopupAnimation->SetTargetObject( this );
		setScale( 0 );
		setVisible( true );
//		connect( m_pPopupAnimation, SIGNAL( signalAnimationFinished( CQmlViewBase*, bool ) ), this, SLOT( slotAnimationFinished( CQmlViewBase*, bool ) ) );
	}
}

void CQmlViewBase::ShowAnimation( float a_fMouseX, float a_fMouseY, int a_iTimeMs )
{
	if ( m_pPopupAnimation )
	{
		m_pPopupAnimation->SetWidgetBasePositionX( a_fMouseX - ( MyCommon::SCREEN_WIDTH / 2 ) );
		m_pPopupAnimation->SetWidgetBasePositionY( a_fMouseY - ( MyCommon::SCREEN_HEIGHT / 2 ) );
		m_pPopupAnimation->StartAnimation( true, a_iTimeMs );
	}
}

void CQmlViewBase::HideAnimation( float a_fMouseX, float a_fMouseY, int a_iTimeMs )
{
	if ( m_pPopupAnimation )
	{
		m_pPopupAnimation->SetWidgetBasePositionX( a_fMouseX - ( MyCommon::SCREEN_WIDTH / 2 ) );
		m_pPopupAnimation->SetWidgetBasePositionY( a_fMouseY - ( MyCommon::SCREEN_HEIGHT / 2 ) );
		m_pPopupAnimation->StartAnimation( false, a_iTimeMs );
	}
}

void CQmlViewBase::slotSendMessage(QString a_strMessage)
{
	a_strMessage.append("#");
	emit signalSendMessage( a_strMessage );
}

void CQmlViewBase::slotAnimationFinished( CQmlViewBase* /*a_pView*/, bool /*a_bShow*/ )
{
}
