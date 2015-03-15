#ifndef CQMLVIEWGALWAN_H
#define CQMLVIEWGALWAN_H

#include "cqmlviewbase.h"

#include "cqmltextbutton.h"
#include "cqmlslider.h"

class CQmlViewGalwan : public CQmlViewBase
{
	Q_OBJECT
public:
	explicit CQmlViewGalwan(QQuickItem *parent = 0);
	virtual void Initialize();
signals:

public slots:
	virtual void slotClicked( CClickableObject* a_pClickedObject );
	virtual void slotClicked(CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY );

private:
	void ManagePlayButtonClicked( float a_fMouseX, float a_fMouseY );
	void ManageBackButtonClicked( float a_fMouseX, float a_fMouseY );
	void ManagePlayVacuumButtonClicked( float a_fMouseX, float a_fMouseY );

	CQmlTextButton*		m_pButtonBack;
	CQmlTextButton*		m_pButtonPlay;
	CQmlTextButton*		m_pButtonPlayVacuum;

	CQmlSlider*		m_pSliderAmplitute;
};

#endif // CQMLVIEWGALWAN_H
