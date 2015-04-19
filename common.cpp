#include "common.h"

#include <QTime>

const QColor MyCommon::COLOR_LIGHT_RED = QColor( 0xff, 0x85, 0x63 );
const QColor MyCommon::COLOR_RED = QColor( "#bf4624" );
const QColor MyCommon::COLOR_DARK_RED = QColor( 0x66, 0x20, 0x0d );

const QColor MyCommon::COLOR_SELEDIN = QColor( "#8dbba6" );
const QColor MyCommon::COLOR_DARK_SELEDIN = QColor( "#6e9d8a" );

const QColor MyCommon::COLOR_SHIT_YELLOW = QColor( "#d7d8a1" );
const QColor MyCommon::COLOR_SHIT_VIOLET = QColor( "#8d9abb" );

const QColor MyCommon::COLOR_LIGHT_VIOLET = QColor( 0xa4, 0x63, 0xff );
const QColor MyCommon::COLOR_VIOLET = QColor( 0x7c, 0x27, 0xa3 );
const QColor MyCommon::COLOR_DARK_VIOLET = QColor( 0x3c, 0x15, 0x6b );

const QColor MyCommon::COLOR_LIGHT_GREEN = QColor( 0xbe, 0xff, 0x63 );
const QColor MyCommon::COLOR_GREEN = QColor( 0x7a, 0xb3, 0x29 );
const QColor MyCommon::COLOR_DARK_GREEN = QColor( 0x3f, 0x5c, 0x11 );

const QColor MyCommon::COLOR_LIGHT_BLUE = QColor( 0xb8, 0xe8, 0xff );
const QColor MyCommon::COLOR_BLUE = QColor( 0x5f, 0xc2, 0xf1 );
const QColor MyCommon::COLOR_DARK_BLUE = QColor( 0x08, 0x60, 0x89 );

const QColor MyCommon::COLOR_LIGHT_BEIGE = QColor( 0xe5, 0xd1, 0xa0 );
const QColor MyCommon::COLOR_BEIGE = QColor( 0xc9, 0xb5, 0x93 );

const QColor MyCommon::COLOR_LIGHT_GREY = QColor( 0xe2, 0xdc, 0xd1 );
const QColor MyCommon::COLOR_GREY = QColor( 0xba, 0xb6, 0xb0 );

const QColor MyCommon::COLOR_LIGHT_KHAKI = QColor( 0xa9, 0x99, 0x74 );
const QColor MyCommon::COLOR_KHAKI = QColor( 0x74, 0x68, 0x52 );

const QString MyCommon::BTN_START_PRESSED = "/img/start_pressed.png";
const QString MyCommon::BTN_START_RELEASED = "/img/start_released.png";

const QString MyCommon::BTN_STOP_PRESSED = "/img/stop_pressed.png";
const QString MyCommon::BTN_STOP_RELEASED = "/img/stop_released.png";

const QString MyCommon::BTN_BACK_VACUUM_PRESSED = "/img/back_vacuum_pressed.png";
const QString MyCommon::BTN_BACK_VACUUM_RELEASED = "/img/back_vacuum_released.png";

const QString MyCommon::FONT_FAMILY_DEFAULT = "Droid Sans Mono";

MyCommon::MyCommon(QObject *parent) :
    QObject(parent)
{
}

int MyCommon::GetRandInt(int low, int high)
{
	// Random number between low and high
	return qrand() % ((high + 1) - low) + low;
}

QColor MyCommon::GetCOLOR_LIGHT_RED() const
{
	return COLOR_LIGHT_RED;
}

QColor MyCommon::GetCOLOR_RED() const
{
	return COLOR_RED;
}

QColor MyCommon::GetCOLOR_DARK_RED() const
{
	return COLOR_DARK_RED;
}

QColor MyCommon::GetCOLOR_SHIT_YELLOW() const
{
	return COLOR_SHIT_YELLOW;
}

QColor MyCommon::GetCOLOR_SHIT_VIOLET() const
{
	return COLOR_SHIT_VIOLET;
}

QColor MyCommon::GetCOLOR_SELEDIN() const
{
	return COLOR_SELEDIN;
}

QColor MyCommon::GetCOLOR_DARK_SELEDIN() const
{
	return COLOR_DARK_SELEDIN;
}

QColor MyCommon::GetCOLOR_LIGHT_VIOLET() const
{
	return COLOR_LIGHT_VIOLET;
}

QColor MyCommon::GetCOLOR_VIOLET() const
{
	return COLOR_VIOLET;
}

QColor MyCommon::GetCOLOR_DARK_VIOLET() const
{
	return COLOR_DARK_VIOLET;
}

QColor MyCommon::GetCOLOR_LIGHT_GREEN() const
{
	return COLOR_LIGHT_GREEN;
}

QColor MyCommon::GetCOLOR_GREEN() const
{
	return COLOR_GREEN;
}

QColor MyCommon::GetCOLOR_DARK_GREEN() const
{
	return COLOR_DARK_GREEN;
}

QColor MyCommon::GetCOLOR_LIGHT_BLUE() const
{
	return COLOR_LIGHT_BLUE;
}

QColor MyCommon::GetCOLOR_BLUE() const
{
	return COLOR_BLUE;
}

QColor MyCommon::GetCOLOR_DARK_BLUE() const
{
	return COLOR_DARK_BLUE;
}

QColor MyCommon::GetCOLOR_LIGHT_BEIGE() const
{
	return COLOR_LIGHT_BEIGE;
}

QColor MyCommon::GetCOLOR_BEIGE() const
{
	return COLOR_BEIGE;
}

QColor MyCommon::GetCOLOR_LIGHT_GREY() const
{
	return COLOR_LIGHT_GREY;
}

QColor MyCommon::GetCOLOR_GREY() const
{
	return COLOR_GREY;
}

QColor MyCommon::GetCOLOR_LIGHT_KHAKI() const
{
	return COLOR_LIGHT_KHAKI;
}

QColor MyCommon::GetCOLOR_KHAKI() const
{
	return COLOR_KHAKI;
}

QString MyCommon::GetBTN_STOP_PRESSED() const
{
	return BTN_STOP_PRESSED;
}

QString MyCommon::GetBTN_STOP_RELEASED() const
{
	return BTN_STOP_RELEASED;
}

QString MyCommon::GetBTN_BACK_VACUUM_PRESSED() const
{
	return BTN_BACK_VACUUM_PRESSED;
}

QString MyCommon::GetBTN_BACK_VACUUM_RELEASED() const
{
	return BTN_BACK_VACUUM_RELEASED;
}

QString MyCommon::GetFONT_FAMILY_DEFAULT() const
{
	return FONT_FAMILY_DEFAULT;
}

QString MyCommon::GetBTN_START_PRESSED() const
{
	return BTN_START_PRESSED;
}

QString MyCommon::GetBTN_START_RELEASED() const
{
	return BTN_START_RELEASED;
}
