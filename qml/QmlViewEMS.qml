import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1
import MyCustoms 1.0

CQmlViewEMS
{
	id: id_viewEMS
	MouseArea
	{
		anchors.fill: id_imagePS
	}
	Image
	{
		id: id_imagePS
		anchors.fill: id_viewEMS
		source: "/img/logo_with_bg.png"
		width: MyQMLEnums.SCREEN_WIDTH - 150
		height: MyQMLEnums.SCREEN_HEIGHT - 300

		ColumnLayout
		{
			id: id_layoutMain
			anchors.fill: id_imagePS
			spacing: 10
			Rectangle
			{
				id: id_title
				objectName: id_viewEMS.objectName + "_Title"
				height: 100
				width: MyQMLEnums.SCREEN_WIDTH
//				color: MyCommon.COLOR_BEIGE
				anchors.top: id_layoutMain.top
				anchors.horizontalCenter: id_layoutMain.horizontalCenter
				color: "blue"
				Text
				{
					id: id_titleText
					anchors.horizontalCenter: id_title.horizontalCenter
					anchors.verticalCenter: id_title.verticalCenter
					font.pointSize: MyQMLEnums.FONT_SIZE_TITLE
					font.family: MyCommon.FONT_FAMILY_DEFAULT
					font.bold: true
					color: "white"
					text: "ElektroStymulacja"
				}

			}

			QmlSlider
			{
				id: id_slider_amplitude
				objectName: id_viewEMS.objectName + "_SliderAmplitude"
				anchors.horizontalCenter: id_layoutMain.horizontalCenter
				Layout.preferredHeight: 50
			}
			QmlSlider
			{
				id: id_slider_pulse_width
				objectName: id_viewEMS.objectName + "_SliderPulseWidth"
				anchors.horizontalCenter: id_layoutMain.horizontalCenter
				Layout.preferredHeight: 50
			}
			QmlSlider
			{
				id: id_slider_frequency
				objectName: id_viewEMS.objectName + "_SliderFrequency"
				anchors.horizontalCenter: id_layoutMain.horizontalCenter
				Layout.preferredHeight: 50
			}
			RowLayout
			{
				id: id_layoutBottom
				anchors.bottom: id_layoutMain.bottom
				anchors.left: id_layoutMain.left
				anchors.right: id_layoutMain.right


				QmlTextButton
				{
					id: id_button_Back
					objectName: id_viewEMS.objectName + "_ButtonBack"

					anchors.bottom: id_layoutBottom.bottom
					anchors.left: id_layoutBottom.left
					anchors.bottomMargin: MyQMLEnums.SCREEN_HEIGHT / 8
					anchors.leftMargin: MyQMLEnums.SCREEN_WIDTH / 60

					height: MyQMLEnums.SCREEN_HEIGHT / 6
					width: MyQMLEnums.SCREEN_WIDTH / 5

					m_pressedColor: MyCommon.COLOR_GREY;
					m_normalColor: MyCommon.COLOR_LIGHT_GREY;
					m_strButtonText: "Powrót"
				}

				QmlTextButton
				{
					id: id_button_Play
					objectName: id_viewEMS.objectName + "_ButtonPlay"

					state: "start"
					anchors.bottom: id_layoutBottom.bottom
					anchors.right: id_layoutBottom.right
					anchors.bottomMargin: MyQMLEnums.SCREEN_HEIGHT / 8
					anchors.rightMargin: MyQMLEnums.SCREEN_WIDTH / 60

					height: MyQMLEnums.SCREEN_HEIGHT / 6
					width: MyQMLEnums.SCREEN_WIDTH / 5

					states:
						[
						State
						{
							name: "start"
							PropertyChanges
							{
								target: id_button_Play;
								m_pressedColor: MyCommon.COLOR_DARK_GREEN;
								m_normalColor: MyCommon.COLOR_GREEN;
								m_strButtonText: "Start"
								objectName: id_viewEMS.objectName + "_ButtonPlay_Start"
							}
						},
						State
						{
							name: "stop"
							PropertyChanges
							{
								target: id_button_Play;
								m_pressedColor: MyCommon.COLOR_DARK_RED;
								m_normalColor: MyCommon.COLOR_RED;
								m_strButtonText: "Stop"
								objectName: id_viewEMS.objectName + "_ButtonPlay_Stop"
							}
						}
					]
				}
			}
		}
	}
	Component.onCompleted:
	{
		id_title.color = MyCommon.COLOR_BEIGE
	}
}
