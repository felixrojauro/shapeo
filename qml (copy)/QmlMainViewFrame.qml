import QtQuick 2.0
import QtQuick.Layouts 1.1
import MyCustoms 1.0

Rectangle
{
    id: id_root
	objectName: "ROOT"
	width: MyQMLEnums.SCREEN_WIDTH
	height: MyQMLEnums.SCREEN_HEIGHT

	QmlMainView
	{
		id: id_mainView
		anchors.fill: id_root
		objectName: id_root.objectName + "_MainView"
	}

}
