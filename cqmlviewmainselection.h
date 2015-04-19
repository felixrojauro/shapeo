#ifndef CQMLVIEWMAINSELECTION_H
#define CQMLVIEWMAINSELECTION_H

#include "cqmlviewbase.h"
#include "cqmltextbutton.h"

class CQmlViewMainSelection : public CQmlViewBase
{
	Q_OBJECT
public:
	explicit CQmlViewMainSelection(QQuickItem *parent = 0);
	virtual void Initialize();

signals:
	void signalShowInfusion( float a_fMouseX, float a_fMouseY );
	void signalShowPeelJet( float a_fMouseX, float a_fMouseY );
	void signalShowShapeo( float a_fMouseX, float a_fMouseY );
public slots:
	virtual void slotClicked( CClickableObject* a_pClickedObject );
	virtual void slotClicked( CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY );

private:

	void ManageButtonInfusionClicked( float a_fMouseX, float a_fMouseY );
	void ManageButtonPeelJetClicked( float a_fMouseX, float a_fMouseY );
	void ManageButtonShapeoClicked( float a_fMouseX, float a_fMouseY );
	CQmlTextButton* m_pButtonInfusion;
	CQmlTextButton* m_pButtonPeelJet;
	CQmlTextButton* m_pButtonQuit;
	CQmlTextButton* m_pButtonShapeo;

};

#endif // CQMLVIEWMAINSELECTION_H
