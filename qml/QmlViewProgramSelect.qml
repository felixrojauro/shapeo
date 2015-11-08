import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1
import MyCustoms 1.0

CQmlViewProgramSelect
{
	id: id_viewProgramSelect
	MouseArea
	{
		anchors.fill: id_imagePS
	}
	Image
	{
		id: id_imagePS
		anchors.fill: id_viewProgramSelect
		source: "/img/logo_with_bg.png"
		sourceSize.width: MyQMLEnums.SCREEN_WIDTH - 150
		sourceSize.height: MyQMLEnums.SCREEN_HEIGHT - 300

		ColumnLayout
		{
			id: id_layoutMain
			anchors.fill: id_imagePS
			Rectangle
			{
				id: id_title
				objectName: id_viewProgramSelect.objectName + "_Title"
				width: MyQMLEnums.SCREEN_WIDTH
				height: 100
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
					text: "Zabiegi tlenowe"
				}
			}

			RowLayout
			{
				id: id_layoutButtons
				anchors.horizontalCenter: id_layoutMain.horizontalCenter
				anchors.verticalCenter: id_layoutMain.verticalCenter
				anchors.margins: 40
				spacing: 20

				QmlTextButton
				{
					id: id_button_Vacuum
					objectName: id_viewProgramSelect.objectName + "_ButtonVacuum"

					height: MyQMLEnums.SCREEN_HEIGHT / 6
					width: MyQMLEnums.SCREEN_WIDTH / 5
				}

				QmlTextButton
				{
					id: id_button_Galwan
					objectName: id_viewProgramSelect.objectName + "_Galwan"

					height: MyQMLEnums.SCREEN_HEIGHT / 6
					width: MyQMLEnums.SCREEN_WIDTH / 5
				}

				QmlTextButton
				{
					id: id_button_EMS
					objectName: id_viewProgramSelect.objectName + "_ButtonEMS"

					height: MyQMLEnums.SCREEN_HEIGHT / 6
					width: MyQMLEnums.SCREEN_WIDTH / 5
				}
				QmlTextButton
				{
					id: id_button_Quit
					objectName: id_viewProgramSelect.objectName + "_ButtonQuit"

					height: MyQMLEnums.SCREEN_HEIGHT / 6
					width: MyQMLEnums.SCREEN_WIDTH / 6
					anchors.right: id_layoutButtons.right
				}
			}
		}
	}
	Component.onCompleted:
	{
		id_title.color = MyCommon.COLOR_RED
	}
}
