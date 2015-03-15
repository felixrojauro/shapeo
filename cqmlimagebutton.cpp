#include "cqmlimagebutton.h"

CQmlImageButton::CQmlImageButton(QQuickItem *parent)
	: CClickableObject(parent)
{
	m_eType = CClickableObject::TYPE_BUTTON;
}

void CQmlImageButton::SetImageReleased(QString a_strImgPath)
{
	if ( m_strImgReleased != a_strImgPath )
	{
		m_strImgReleased = a_strImgPath;
		emit signalImageReleasedChanged();
	}
}

QString CQmlImageButton::GetImageReleased() const
{
	return m_strImgReleased;
}

void CQmlImageButton::SetImagePressed(QString a_strImgPath)
{
	if ( m_strImgPressed != a_strImgPath )
	{
		m_strImgPressed = a_strImgPath;
		emit signalImagePressedChanged();
	}
}

QString CQmlImageButton::GetImagePressed() const
{
	return m_strImgPressed;
}
