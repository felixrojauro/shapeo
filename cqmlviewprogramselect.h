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
	void signalShowVacuum( float a_fMouseX, float a_fMouseY );
	void signalShowGalwan( float a_fMouseX, float a_fMouseY );
	void signalShowEMS( float a_fMouseX, float a_fMouseY );
public slots:
	virtual void slotClicked( CClickableObject* a_pClickedObject );
	virtual void slotClicked( CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY );

private:

	void ManageButtonEMSClicked( float a_fMouseX, float a_fMouseY );
	void ManageButtonGalwanClicked( float a_fMouseX, float a_fMouseY );
	void ManageButtonVacuumClicked( float a_fMouseX, float a_fMouseY );
	CQmlTextButton* m_pButtonEMS;
	CQmlTextButton* m_pButtonGalwan;
	CQmlTextButton* m_pButtonQuit;
	CQmlTextButton* m_pButtonVacuum;

};

#endif // CQMLVIEWPROGRAMSELECT_H
