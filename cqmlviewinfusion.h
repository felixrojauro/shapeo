#ifndef CQMLVIEWINFUSION_H
#define CQMLVIEWINFUSION_H

#include "cqmlviewbase.h"
#include "cqmltextbutton.h"

class CQmlViewInfusion : public CQmlViewBase
{
	Q_OBJECT
public:
	explicit CQmlViewInfusion(QQuickItem *parent = 0);
	virtual void Initialize();

signals:

public slots:
	virtual void slotClicked( CClickableObject* a_pClickedObject );
	virtual void slotClicked(CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY );
private:

	void ManagePlayButtonClicked( float a_fMouseX, float a_fMouseY );
	void ManageBackButtonClicked( float a_fMouseX, float a_fMouseY );
	CQmlTextButton* m_pButtonBack;
	CQmlTextButton* m_pButtonPlay;
};

#endif // CQMLVIEWINFUSION_H
