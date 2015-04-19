import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1
import MyCustoms 1.0

CQmlMainView
{
	id: id_mainView

	QmlViewVacuum
	{
		id: id_vacuum
		objectName: id_mainView.objectName + "_ViewVacuum"
		x: 0
		y: 0
		width: id_mainView.width
		height: id_mainView.height
//		anchors.fill: id_mainView
	}
	QmlViewGalwan
	{
		id: id_galwan
		objectName: id_mainView.objectName + "_ViewGalwan"
		x: 0
		y: 0
		width: id_mainView.width
		height: id_mainView.height
//		anchors.fill: id_mainView
	}
	QmlViewEMS
	{
		id: id_ems
		objectName: id_mainView.objectName + "_ViewEMS"
		x: 0
		y: 0
		width: id_mainView.width
		height: id_mainView.height
//		anchors.fill: id_mainView
	}
	QmlViewProgramSelect
	{
		id: id_ProgramSelect
		objectName: id_mainView.objectName + "_ViewProgramSelect"
		x: 0
		y: 0
		width: id_mainView.width
		height: id_mainView.height
//		anchors.fill: id_mainView
	}
	QmlViewMainSelection
	{
		id: id_MainSelection
		objectName: id_mainView.objectName + "_ViewMainSelection"
		x: 0
		y: 0
		width: id_mainView.width
		height: id_mainView.height
//		anchors.fill: id_mainView
	}
	QmlConnectionControl
	{
		id: id_connectionControl
		objectName: id_mainView.objectName + "_ConnectionControl"
		z: 10
		anchors.bottom: id_mainView.bottom
		anchors.horizontalCenter: id_mainView.horizontalCenter
		width: MyQMLEnums.SCREEN_WIDTH / 3
		height: MyQMLEnums.SCREEN_HEIGHT / 6
		visible: true
		state: id_mainView.m_strAppState
	}


}
