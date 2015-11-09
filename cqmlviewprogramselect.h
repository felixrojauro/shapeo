#ifndef CQMLVIEWPROGRAMSELECT_H
#define CQMLVIEWPROGRAMSELECT_H

#include "cqmlviewbase.h"
#include "cqmltextbutton.h"

class CQmlViewProgramSelect : public CQmlViewBase
{
	Q_OBJECT
public:
	explicit CQmlViewProgramSelect(QQuickItem *parent = 0);
	virtual void Initialize();

signals:
	void signalShowInfusion( float a_fMouseX, float a_fMouseY );
	void signalShowOxyTreatment( float a_fMouseX, float a_fMouseY );
	void signalShowEMS( float a_fMouseX, float a_fMouseY );
public slots:
	virtual void slotClicked( CClickableObject* a_pClickedObject );
	virtual void slotClicked( CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY );

private:

	void ManageButtonEMSClicked( float a_fMouseX, float a_fMouseY );
	void ManageButtonInfusionClicked( float a_fMouseX, float a_fMouseY );
	void ManageButtonOxyTreatmentClicked( float a_fMouseX, float a_fMouseY );
	void ManageButtonBackClicked(float a_fMouseX, float a_fMouseY);

	CQmlTextButton* m_pButtonEMS;
	CQmlTextButton* m_pButtonOxyTreatment;
	CQmlTextButton* m_pButtonBack;
	CQmlTextButton* m_pButtonInfusion;

};

#endif // CQMLVIEWPROGRAMSELECT_H
