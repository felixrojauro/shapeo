#include "cqmltextbutton.h"

#include "common.h"

CQmlTextButton::CQmlTextButton(QQuickItem *parent)
	: CClickableObject(parent)
	, m_normalColor( QColor() )
	, m_pressedColor( QColor() )
	, m_strButtonText( "txt" )
{
	m_eType = CClickableObject::TYPE_BUTTON;
	SetNormalColor( MyCommon::COLOR_GREEN );
	SetPressedColor( MyCommon::COLOR_DARK_GREEN );
}

void CQmlTextButton::SetNormalColor(QColor a_normalColor)
{
	if ( m_normalColor != a_normalColor )
	{
		m_normalColor = a_normalColor;
		emit signalNormalColorChanged();
	}
}

QColor CQmlTextButton::GetNormalColor() const
{
	return m_normalColor;
}

void CQmlTextButton::SetPressedColor(QColor a_pressedColor)
{
	if ( m_pressedColor != a_pressedColor )
	{
		m_pressedColor = a_pressedColor;
		emit signalPressedColorChanged();
	}
}

QColor CQmlTextButton::GetPressedColor() const
{
	return m_pressedColor;
}

void CQmlTextButton::SetButtonText(QString a_strButtonText)
{
	if ( m_strButtonText != a_strButtonText )
	{
		m_strButtonText = a_strButtonText;
		emit signalButtonTextChanged();
	}
}

QString CQmlTextButton::GetButtonText() const
{
	return m_strButtonText;
}
