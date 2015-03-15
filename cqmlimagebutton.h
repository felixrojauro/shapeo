#ifndef CQMLIMAGEBUTTON_H
#define CQMLIMAGEBUTTON_H

#include "cclickableobject.h"

class CQmlImageButton : public CClickableObject
{
	Q_OBJECT

	Q_PROPERTY( QString m_strImgReleased READ GetImageReleased WRITE SetImageReleased NOTIFY signalImageReleasedChanged )
	Q_PROPERTY( QString m_strImgPressed READ GetImagePressed WRITE SetImagePressed NOTIFY signalImagePressedChanged )

public:
	explicit CQmlImageButton(QQuickItem *parent = 0);

	void SetImageReleased( QString a_strImgPath );
	QString GetImageReleased() const;

	void SetImagePressed( QString a_strImgPath );
	QString GetImagePressed() const;

signals:
	void signalImageReleasedChanged();
	void signalImagePressedChanged();
public slots:

private:
	QString m_strImgReleased;
	QString m_strImgPressed;
};

#endif // CQMLIMAGEBUTTON_H
