#ifndef CFULLSCREENPOPUPANIMATION_H
#define CFULLSCREENPOPUPANIMATION_H

// Ot
#include <QObject>
#include <QQuickItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPointer>

class CQmlViewBase;
class CFullScreenPopupAnimation : public QObject
{
	Q_OBJECT

public:
	/////////////////
	// Methods
	CFullScreenPopupAnimation( QObject* a_pParent = 0 );									//!< Constructor
	virtual ~CFullScreenPopupAnimation();													//!< Destructor

	inline void SetWidgetBasePositionX( float a_iValue );										//!< Setter for animated widget base X position
	inline void SetWidgetBasePositionY( float a_iValue );										//!< Setter for animated widget base Y position

	inline void SetTargetObject( CQmlViewBase* a_pTargetObject );							//!< Setter for object which should be animated

	bool PrepareAnimation();																//!< Prepare animations settings
	bool StartAnimation( bool a_bShowPopup, int a_iDuration );								//!< Start already prepared animations

signals:
	//! Signal is emitted when showing/hiding animation is finished. It gives a popup that is animating and bool that tells
	//  if popup is showing up (true)  or hiding up (false)
	void signalAnimationFinished( CQmlViewBase* a_pTargetObject, bool a_bShow );

private slots:
	//! Reaction on animation finish
	void slotAnimationFinished();

private:
	/////////////////
	// Methods
	void ResetTargetWidgetPosition();

	/////////////////
	// Attributes
	int 									m_fWidgetBasePositionX;							//!< widget base X position
	int 									m_fWidgetBasePositionY;							//!< widget base Y position

	CQmlViewBase*							m_pTargetWidget;								//!< widget which to resize
	QPointer<QPropertyAnimation>			m_pRepositionXAnimation;						//!< X position animation
	QPointer<QPropertyAnimation>			m_pRepositionYAnimation;						//!< Y position animation
	QPointer<QPropertyAnimation>			m_pScaleAnimation;								//!< scale change animation

	QPointer<QParallelAnimationGroup>		m_pWidgetAnimation;								//!< widget popup show/hide animation container
	bool m_bShow;																			//!< Show or hide animation
};

/////////////////////////////////////////////////////////////////////////////
/*!
//\par		Description:
//			Sets base widget position X
//
//\par		Parameters:
//\arg		[IN]	\b	a_iValue	- new position X
//
//\par		Return value:
//			None.
*/
inline void CFullScreenPopupAnimation::SetWidgetBasePositionX( float a_iValue )
{
	m_fWidgetBasePositionX = a_iValue;
}

/////////////////////////////////////////////////////////////////////////////
/*!
//\par		Description:
//			Sets base widget position Y
//
//\par		Parameters:
//\arg		[IN]	\b	a_iValue	- new position Y
//
//\par		Return value:
//			None.
*/
inline void CFullScreenPopupAnimation::SetWidgetBasePositionY( float a_iValue )
{
	m_fWidgetBasePositionY = a_iValue;
}

/////////////////////////////////////////////////////////////////////////////
/*!
//\par		Description:
//			Setter for object which should be animated
//
//\par		Parameters:
//\arg		[IN]	\b	a_pTargetObject	- object to animate
//
//\par		Return value:
//			None.
*/
void CFullScreenPopupAnimation::SetTargetObject( CQmlViewBase* a_pTargetObject )
{
	m_pTargetWidget = a_pTargetObject;
}

#endif // CFULLSCREENPOPUPANIMATION_H


