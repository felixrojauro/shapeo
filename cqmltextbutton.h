#ifndef CQMLTEXTBUTTON_H
#define CQMLTEXTBUTTON_H

#include "cclickableobject.h"

class CQmlTextButton : public CClickableObject
{
	Q_OBJECT

	Q_PROPERTY( QColor m_normalColor READ GetNormalColor WRITE SetNormalColor NOTIFY signalNormalColorChanged )
	Q_PROPERTY( QColor m_pressedColor READ GetPressedColor WRITE SetPressedColor NOTIFY signalPressedColorChanged )
	Q_PROPERTY( QString m_strButtonText READ GetButtonText WRITE SetButtonText NOTIFY signalButtonTextChanged )

public:
	explicit CQmlTextButton(QQuickItem *parent = 0);

	void SetNormalColor( QColor a_normalColor );
	QColor GetNormalColor() const;

	void SetPressedColor( QColor a_pressedColor );
	QColor GetPressedColor() const;

	void SetButtonText( QString a_strButtonText );
	QString GetButtonText() const;

signals:
	void signalNormalColorChanged();
	void signalPressedColorChanged();
	void signalButtonTextChanged();
public slots:

private:
	QColor m_normalColor;
	QColor m_pressedColor;

	QString m_strButtonText;
};

#endif // CQMLTEXTBUTTON_H
