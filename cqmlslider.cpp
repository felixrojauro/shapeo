#include "cqmlslider.h"

CQmlSlider::CQmlSlider(QQuickItem *parent)
	: CClickableObject(parent)
	, m_iValue( 0 )
{
	m_eType = CClickableObject::TYPE_SLIDER;
}

int CQmlSlider::GetValue() const
{
	return m_iValue;
}

void CQmlSlider::SetValue(int a_newValue)
{
	if ( m_iValue != a_newValue )
	{
		m_iValue = a_newValue;
		emit signalValueChanged();
		emit signalClicked( this );
	}
}

QColor CQmlSlider::GetColorBorder() const
{
	return m_colorBorder;
}

void CQmlSlider::SetColorBorder(QColor a_newColor)
{
	if ( a_newColor != m_colorBorder )
	{
		m_colorBorder = a_newColor;
		emit signalColorBorderChanged();
	}
}

QColor CQmlSlider::GetColorHandleReleased() const
{
	return m_colorHandleReleased;
}

void CQmlSlider::SetColorHandleReleased(QColor a_newColor)
{
	if ( a_newColor != m_colorHandleReleased )
	{
		m_colorHandleReleased = a_newColor;
		emit signalColorHandleReleasedChanged();
	}
}

QColor CQmlSlider::GetColorHandlePressed() const
{
	return m_colorHandlePressed;
}

void CQmlSlider::SetColorHandlePressed(QColor a_newColor)
{
	if ( a_newColor != m_colorHandlePressed )
	{
		m_colorHandlePressed = a_newColor;
		emit signalColorHandlePressedChanged();
	}
}

QColor CQmlSlider::GetColorBase() const
{
	return m_colorBase;
}

void CQmlSlider::SetColorBase(QColor a_newColor)
{
	if ( a_newColor != m_colorBase )
	{
		m_colorBase = a_newColor;
		emit signalColorBaseChanged();
	}
}

int CQmlSlider::GetMinimumValue() const
{
	return m_iMinimumValue;
}

void CQmlSlider::SetMinimumValue(int a_newValue)
{
	if ( m_iMinimumValue != a_newValue )
	{
		m_iMinimumValue = a_newValue;
		emit signalMinimumValueChanged();
	}
}

int CQmlSlider::GetMaximumValue() const
{
	return m_iMaximumValue;
}

void CQmlSlider::SetMaximumValue(int a_newValue)
{
	if ( m_iMaximumValue != a_newValue )
	{
		m_iMaximumValue = a_newValue;
		emit signalMaximumValueChanged();
	}
}

int CQmlSlider::GetStepSize() const
{
	return m_iStepSize;
}

void CQmlSlider::SetStepSize(int a_newValue)
{
	if ( m_iStepSize != a_newValue )
	{
		m_iStepSize = a_newValue;
		emit signalStepSizeChanged();
	}
}

QString CQmlSlider::GetSliderName() const
{
	return m_strSliderName;
}

void CQmlSlider::SetSliderName(const QString a_strNewName)
{
	if ( m_strSliderName != a_strNewName )
	{
		m_strSliderName = a_strNewName;
		emit signalSliderNameChanged();
	}
}

QString CQmlSlider::GetValueSuffix() const
{
	return m_strValueSuffix;
}

void CQmlSlider::SetValueSuffix(const QString a_strNewSuffix)
{
	if ( m_strValueSuffix != a_strNewSuffix )
	{
		m_strValueSuffix = a_strNewSuffix;
		emit signalValueSuffixChanged();
	}
}
