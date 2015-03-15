#ifndef CQMLSLIDER_H
#define CQMLSLIDER_H

#include <QQuickItem>

#include "cclickableobject.h"

class CQmlSlider : public CClickableObject
{
	Q_OBJECT

	Q_PROPERTY( int m_iValue READ GetValue WRITE SetValue NOTIFY signalValueChanged )

	Q_PROPERTY( QColor m_colorBorder READ GetColorBorder WRITE SetColorBorder NOTIFY signalColorBorderChanged )
	Q_PROPERTY( QColor m_colorHandleReleased READ GetColorHandleReleased WRITE SetColorHandleReleased NOTIFY signalColorHandleReleasedChanged )
	Q_PROPERTY( QColor m_colorHandlePressed READ GetColorHandlePressed WRITE SetColorHandlePressed NOTIFY signalColorHandlePressedChanged )
	Q_PROPERTY( QColor m_colorBase READ GetColorBase WRITE SetColorBase NOTIFY signalColorBaseChanged )

	Q_PROPERTY( int m_iMinimumValue READ GetMinimumValue WRITE SetMinimumValue NOTIFY signalMinimumValueChanged )
	Q_PROPERTY( int m_iMaximumValue READ GetMaximumValue WRITE SetMaximumValue NOTIFY signalMaximumValueChanged )
	Q_PROPERTY( int m_iStepSize READ GetStepSize WRITE SetStepSize NOTIFY signalStepSizeChanged )

	Q_PROPERTY( QString m_strSliderName READ GetSliderName WRITE SetSliderName NOTIFY signalSliderNameChanged )
	Q_PROPERTY( QString m_strValueSuffix READ GetValueSuffix WRITE SetValueSuffix NOTIFY signalValueSuffixChanged )

public:
	explicit CQmlSlider(QQuickItem *parent = 0);

	int GetValue() const;
	void SetValue( int a_newValue );

	QColor GetColorBorder() const;
	void SetColorBorder( QColor a_newColor );

	QColor GetColorHandleReleased() const;
	void SetColorHandleReleased( QColor a_newColor );

	QColor GetColorHandlePressed() const;
	void SetColorHandlePressed( QColor a_newColor );

	QColor GetColorBase() const;
	void SetColorBase( QColor a_newColor );

	int GetMinimumValue() const;
	void SetMinimumValue( int a_newValue );

	int GetMaximumValue() const;
	void SetMaximumValue( int a_newValue );

	int GetStepSize() const;
	void SetStepSize( int a_newValue );

	QString GetSliderName() const;
	void SetSliderName( const QString a_strNewName );

	QString GetValueSuffix() const;
	void SetValueSuffix( const QString a_strNewSuffix );

signals:
	void signalValueChanged();

	void signalColorBorderChanged();
	void signalColorHandleReleasedChanged();
	void signalColorHandlePressedChanged();
	void signalColorBaseChanged();

	void signalMinimumValueChanged();
	void signalMaximumValueChanged();
	void signalStepSizeChanged();

	void signalSliderNameChanged();
	void signalValueSuffixChanged();

public slots:

private:
	int m_iValue;

	QColor m_colorBorder;
	QColor m_colorHandleReleased;
	QColor m_colorHandlePressed;
	QColor m_colorBase;

	int m_iMinimumValue;
	int m_iMaximumValue;
	int m_iStepSize;

	QString m_strSliderName;
	QString m_strValueSuffix;
};

#endif // CQMLSLIDER_H
