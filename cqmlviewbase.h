#ifndef CQMLVIEWBASE_H
#define CQMLVIEWBASE_H

#include <QQuickItem>
#include <QDebug>

#include "cclickableobject.h"
#include "cfullscreenpopupanimation.h"
#include "common.h"

class CQmlViewBase : public QQuickItem
{
	Q_OBJECT
public:
	explicit CQmlViewBase(QQuickItem *parent = 0);
	virtual void Initialize() = 0;
	virtual void ShowAnimation( float a_fMouseX, float a_fMouseY, int a_iTimeMs = 500 );
	virtual void HideAnimation( float a_fMouseX, float a_fMouseY, int a_iTimeMs = 500 );

signals:
	void signalSendMessage( QString a_strMessage );
	void signalBackToProgramSelectView( float a_fMouseX, float a_fMouseY );
public slots:
	virtual void slotSendMessage( QString a_strMessage );
	virtual void slotClicked( CClickableObject* a_pClickedObject ) = 0;
	virtual void slotClicked(CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY ) = 0;
	virtual void slotAnimationFinished( CQmlViewBase* a_pView, bool a_bShow );
protected:
	CFullScreenPopupAnimation* m_pPopupAnimation;

};

#endif // CQMLVIEWBASE_H
