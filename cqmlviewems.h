#ifndef CQMLVIEWEMS_H
#define CQMLVIEWEMS_H

#include "cqmlviewbase.h"
#include "cqmlslider.h"
#include "cqmltextbutton.h"

class CQmlViewEMS : public CQmlViewBase
{
	Q_OBJECT
public:
	explicit CQmlViewEMS(QQuickItem *parent = 0);
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

	CQmlSlider*		m_pSliderAmplitute;
	CQmlSlider*		m_pSliderFrequency;
	CQmlSlider*		m_pSliderPulseWidth;
};

#endif // CQMLVIEWEMS_H
