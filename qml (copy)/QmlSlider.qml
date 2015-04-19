import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1
import MyCustoms 1.0

CQmlSlider
{
	id: id_slider_package
	Row
	{
		id: id_rowLayout
		anchors.centerIn: id_slider_package
		spacing: MyQMLEnums.SCREEN_WIDTH / 100

		Text
		{
			id: id_sliderName
			anchors.verticalCenter: id_slider.verticalCenter
			width: MyQMLEnums.SCREEN_WIDTH / 4

			font.bold: true
			font.pointSize: MyQMLEnums.FONT_SIZE_SLIDER_DESCRIPTION
			font.family: MyCommon.FONT_FAMILY_DEFAULT

			color: id_slider_package.m_colorBase
			text: id_slider_package.m_strSliderName
		}
		Slider
		{
			id: id_slider
			property real sliderWidth: MyQMLEnums.SCREEN_WIDTH / 2
			property real sliderHeight: MyQMLEnums.SCREEN_HEIGHT / 20
			property real sliderRadius: sliderHeight / 4
			objectName: id_slider_package.objectName + "_SliderItem"

			value: id_slider_package.m_iValue
			minimumValue: id_slider_package.m_iMinimumValue
			maximumValue: id_slider_package.m_iMaximumValue
			stepSize: id_slider_package.m_iStepSize

			style: SliderStyle
			{
				groove: Rectangle
				{
					implicitWidth: id_slider.sliderWidth
					implicitHeight: id_slider.sliderHeight
					gradient: Gradient
					{
						GradientStop { position: 1.0; color: id_slider_package.m_colorBase }
						GradientStop { position: 0.0; color: Qt.darker( id_slider_package.m_colorBase, 2.0 ) }
					}
					radius: id_slider.sliderRadius
				}
				handle: Rectangle
				{
					anchors.centerIn: parent
					gradient: Gradient
					{
						GradientStop { position: 0.0; color: control.pressed ? id_slider_package.m_colorHandlePressed : id_slider_package.m_colorHandleReleased }
						GradientStop { position: 1.0; color: control.pressed ? Qt.darker( id_slider_package.m_colorHandlePressed, 2.0 ) : Qt.darker( id_slider_package.m_colorHandleReleased, 2.0 ) }
					}
					implicitWidth: id_slider.sliderHeight * 1.5
					implicitHeight: id_slider.sliderHeight * 1.5
					radius: id_slider.sliderRadius
				}
			}
			onValueChanged:
			{
				id_slider_package.m_iValue = value
			}
		}
		Text
		{
			id: id_text
			anchors.verticalCenter: id_slider.verticalCenter
			width: MyQMLEnums.SCREEN_WIDTH / 20

			font.bold: true
			font.pointSize: MyQMLEnums.FONT_SIZE_SLIDER_DESCRIPTION
			font.family: MyCommon.FONT_FAMILY_DEFAULT

			color: id_slider_package.m_colorBase
			text: id_slider.value + " " + id_slider_package.m_strValueSuffix

		}
	}
}
