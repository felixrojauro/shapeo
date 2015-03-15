import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import MyCustoms 1.0

CQmlTextButton
{
	id: id_button_package

	MouseArea
	{
		id: id_buttonMouseArea
		objectName: id_button_package.objectName + "_MouseArea"

		anchors.fill: id_button_package
		onClicked:
		{
			signalClicked( id_button_package, mapToItem( null, mouseX, mouseY ).x, mapToItem( null, mouseX, mouseY ).y )
		}
	}
	Rectangle
	{
		id: id_buttonBackground

		anchors.fill: id_button_package
		gradient: Gradient
		{
			GradientStop { position: 0.0; color: id_buttonMouseArea.pressed ? id_button_package.m_pressedColor : id_button_package.m_normalColor }
			GradientStop { position: 1.0; color: id_buttonMouseArea.pressed ? Qt.darker( id_button_package.m_pressedColor, 2.0 ) : Qt.darker( id_button_package.m_normalColor, 2.0 ) }
		}

		radius: 5
		Text
		{
			id: id_buttonText
			text: m_strButtonText
			color: "white"
			font.pointSize: MyQMLEnums.FONT_SIZE_BUTTON
			font.family: MyCommon.FONT_FAMILY_DEFAULT
			font.bold: true
			anchors
			{
				centerIn: id_buttonBackground
			}
		}
	}

}
