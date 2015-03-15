#include "cclickableobject.h"

CClickableObject::CClickableObject(QQuickItem *parent)
	: QQuickItem(parent)
	, m_bActive( true )
{
}

void CClickableObject::SetActive(bool a_bActive)
{
	if ( a_bActive != m_bActive )
	{
		m_bActive = a_bActive;
		emit signalActiveChanged();
	}
}

bool CClickableObject::GetActive() const
{
	return m_bActive;
}
