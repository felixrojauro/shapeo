TEMPLATE = app

QT += qml quick androidextras widgets core gui

TARGET = SHAPEO3
SOURCES += main.cpp \
    clistitem.cpp \
    cqmlmainviewframe.cpp \
	cqmlmainview.cpp \
	common.cpp \
    cqmlslider.cpp \
	cqmlviewvacuum.cpp \
	cqmlviewgalwan.cpp \
	cqmlviewems.cpp \
    cqmlviewbase.cpp \
    cclickableobject.cpp \
	cqmlviewprogramselect.cpp \
	cqmlviewmainselection.cpp \
	android_bt/androidrfcomm.cpp \
	android_bt/candroidrfcommconnector.cpp \
    cqmlimagebutton.cpp \
    cqmltextbutton.cpp \
    cfullscreenpopupanimation.cpp \
    cqmlviewpeeljet.cpp \
    cqmlviewinfusion.cpp

HEADERS += \
    clistitem.h \
    cqmlmainviewframe.h \
	cqmlmainview.h \
	common.h \
    cqmlslider.h \
	cqmlviewvacuum.h \
	cqmlviewgalwan.h \
	cqmlviewems.h \
    cqmlviewbase.h \
    cclickableobject.h \
	cqmlviewprogramselect.h \
	cqmlviewmainselection.h \
	android_bt/androidrfcomm.h \
	android_bt/candroidrfcommconnector.h \
    cqmlimagebutton.h \
    cqmltextbutton.h \
    cfullscreenpopupanimation.h \
    cqmlviewpeeljet.h \
    cqmlviewinfusion.h

RESOURCES += \
    resourceFile.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

CONFIG += mobility

MOBILITY =

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android_bt/manifest

OTHER_FILES += android_bt/manifest/AndroidManifest.xml
