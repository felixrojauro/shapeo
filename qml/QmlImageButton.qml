import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import MyCustoms 1.0

CQmlImageButton
{
	id: id_button_package

	height: id_buttonImage.height
	width: id_buttonImage.width
	state: "start"
	MouseArea
	{
		id: id_buttonMouseArea
		objectName: id_button_package.objectName + "_MouseArea"

		anchors.fill: id_button_package
		onClicked: signalClicked( id_button_package )
	}

	Image
	{
		id: id_buttonImage
		objectName: id_button_package.objectName + "_Image"
		source: id_buttonMouseArea.pressed ? id_button_package.m_strImgPressed : id_button_package.m_strImgReleased
	}
}
