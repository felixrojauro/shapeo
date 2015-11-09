#include "candroidrfcommconnector.h"

#include <QCoreApplication>
#include <unistd.h>

const QString CAndroidRFCOMMConnector::DEVICE_NAME = "HC-06";
const QString CAndroidRFCOMMConnector::DEVICE_ANSWER_PREFIX = "ANSWER";

CAndroidRFCOMMConnector::CAndroidRFCOMMConnector(QObject *parent)
	: QObject(parent)
{
	m_timerAnswerMonitor.setInterval( 200 );
	connect( &m_timerAnswerMonitor, SIGNAL(timeout()), this, SLOT( slotMonitorAnswer()));
	m_timerAnswerMonitor.start();
}

CAndroidRFCOMMConnector::~CAndroidRFCOMMConnector()
{
	m_timerAnswerMonitor.stop();
	disconnect( &m_timerAnswerMonitor, SIGNAL(timeout()), this, SLOT( slotMonitorAnswer()));
	rfcomm.disconnect();
}

bool CAndroidRFCOMMConnector::slotConnect()
{
	qDebug()<<"@@@@@@@@@@@@ CONNECTING STARTED";
	emit signalDuringConnection( true );
	if ( !CheckIfMyDeviceIsAvailable() )
	{
		return false;
	}
	if ( !rfcomm.isConnected() )
	{
		rfcomm.connect( DEVICE_NAME );
	}
	if ( !rfcomm.isConnected() )
	{
		rfcomm.connect( "=HC06" );
	}
	emit signalDuringConnection( false );
	emit signalConnectFinished( rfcomm.isConnected() );
	qDebug()<<"@@@@@@@@@@@@ CONNECTING FINISHED: "<<rfcomm.isConnected();
	return rfcomm.isConnected();

}

void CAndroidRFCOMMConnector::slotDisconnect()
{
	qDebug()<<"@@@@@@@@@@@@ DISCONNECTING STARTED";
	if ( rfcomm.isConnected() )
	{
		rfcomm.disconnect();
	}
	while( rfcomm.isConnected() );
	emit signalDisconnectFinished();
	qDebug()<<"@@@@@@@@@@@@ DISCONNECTING FINISHED";
}

void CAndroidRFCOMMConnector::slotProcess()
{
	while( 1 )
	{
		QCoreApplication::processEvents();
		usleep( 10000 );
	}
}

void CAndroidRFCOMMConnector::slotSendMessage(const QString a_strMessage)
{
	qDebug()<<"send message: "<<a_strMessage;
	if ( rfcomm.isConnected() )
	{
		rfcomm.sendLine( a_strMessage );
	}
	else
	{
//		qDebug()<<"not connected";
	}
}

void CAndroidRFCOMMConnector::slotMonitorAnswer()
{
	if ( rfcomm.isConnected() )
	{
		m_strDeviceAnswer += QString::fromLocal8Bit( rfcomm.receive( 1000, 10 ) );
		if ( m_strDeviceAnswer.contains( DEVICE_ANSWER_PREFIX ) && m_strDeviceAnswer.contains( "$") )
		{
			emit signalReceivedMessage( m_strDeviceAnswer );
//			qDebug()<<"device answer was: "<<m_strDeviceAnswer;
//			qDebug()<<"cleared it.";
			m_strDeviceAnswer.clear();
		}
	}
}

bool CAndroidRFCOMMConnector::CheckIfMyDeviceIsAvailable()
{
	if (rfcomm.isEnabled())
	{
		QMap<QString,QString> map=rfcomm.getPairedDevices();
		QMapIterator<QString,QString> iterator(map);
		while (iterator.hasNext())
		{
			iterator.next();
			if( iterator.value().contains( DEVICE_NAME ) || iterator.value().contains( "=HC06" ) )
			{
//				qDebug()<<"found the device you are looking for";
				return true;
			}
		}
	}
	return false;
}
