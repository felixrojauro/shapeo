#ifndef CCLICKABLEOBJECT_H
#define CCLICKABLEOBJECT_H

#include <QQuickItem>
#include <QDebug>

class CClickableObject : public QQuickItem
{
	Q_OBJECT

	Q_PROPERTY( bool m_bActive READ GetActive WRITE SetActive NOTIFY signalActiveChanged )
public:
	enum EItemType
	{ TYPE_UNKNOWN
	, TYPE_BUTTON
	, TYPE_SLIDER
	};
	explicit CClickableObject(QQuickItem *parent = 0);

	EItemType m_eType;

	virtual void SetActive( bool a_bActive );
	bool GetActive() const;

signals:
	void signalClicked( CClickableObject* a_pClickedObject );
	void signalClicked( CClickableObject* a_pClickedObject, float a_fMouseX, float a_fMouseY );
	void signalActiveChanged();

public slots:

protected:
	bool m_bActive;

};

#endif // CCLICKABLEOBJECT_H
