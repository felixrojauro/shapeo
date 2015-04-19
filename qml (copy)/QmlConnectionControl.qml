import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import MyCustoms 1.0

Item
{
	id: id_control_package
	property string m_strImagePath;
	property string m_strTitle;
	property string m_strDescription;
	property color m_colorTextTitle;
	property color m_colorDescription;

	anchors.bottomMargin: 90

	states:
	[
		State
		{
			name: "unknown"
			PropertyChanges
			{
				target: id_control_package
				m_strImagePath: "/img/bluetooth_gray.png"
				m_strTitle: "Brak danych!"
				m_strDescription: "Uruchom ten program\nponownie."
				m_colorTextTitle: "red"
				m_colorDescription: "red"
				objectName: id_control_package.objectName + "_Unknown"
			}
			PropertyChanges
			{
				target: id_errorTimer
				running: true
			}
		},
		State
		{
			name: "no_connection"
			PropertyChanges
			{
				target: id_control_package
				m_strImagePath: "/img/bluetooth_red.png"
				m_strTitle: "Błąd połączenia!"
				m_strDescription: "Uruchom urządzenie\nponownie."
				m_colorTextTitle: "red"
				m_colorDescription: "red"
				objectName: id_control_package.objectName + "_Bad"
			}
			PropertyChanges
			{
				target: id_errorTimer
				running: true
			}
		},
		State
		{
			name: "connection_ok"
			PropertyChanges
			{
				target: id_control_package
				m_strImagePath: "/img/bluetooth_blue.png"
				m_strTitle: "Komunikacja OK!"
				m_strDescription: ""
				m_colorTextTitle: "steelblue"
				m_colorDescription: "steelblue"
				objectName: id_control_package.objectName + "_Ok"
				visible: true
			}
			PropertyChanges
			{
				target: id_errorTimer
				running: false
			}
		}
	]

	Timer
	{
		id: id_errorTimer
		interval: 250; running: false; repeat: true
		onTriggered:
		{
			id_control_package.visible ? id_control_package.visible = false : id_control_package.visible = true
		}
	}

	Text
	{
		id: id_connectionIndicationTitle
		anchors.top: id_control_package.top
		anchors.left: id_control_package.left
		font.pointSize: MyQMLEnums.FONT_SIZE_TITLE
		font.family: MyCommon.FONT_FAMILY_DEFAULT
		font.bold: true
		text: id_control_package.m_strTitle
		color: id_control_package.m_colorTextTitle
	}
	Text
	{
		id: id_connectionIndicationDescription
		anchors.bottom: id_control_package.bottom
		anchors.left: id_control_package.left
		font.pointSize: MyQMLEnums.FONT_SIZE_CONNECTION_TEXT
		font.family: MyCommon.FONT_FAMILY_DEFAULT
		font.bold: true
		text: id_control_package.m_strDescription
		color: id_control_package.m_colorDescription
	}
	Image
	{
		id: id_connectionIndicationPNG
		anchors.right: id_control_package.right
		anchors.verticalCenter: id_control_package.verticalCenter
		source: id_control_package.m_strImagePath
		scale: 1.4
		visible: true
	}

}
