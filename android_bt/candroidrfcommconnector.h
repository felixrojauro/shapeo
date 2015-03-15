#ifndef CANDROIDRFCOMMCONNECTOR_H
#define CANDROIDRFCOMMCONNECTOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>

#include "androidrfcomm.h"

class CAndroidRFCOMMConnector : public QObject
{
	Q_OBJECT

public:
	static const QString DEVICE_NAME;
	static const QString DEVICE_ANSWER_PREFIX;

	explicit CAndroidRFCOMMConnector(QObject *parent = 0);
	virtual ~CAndroidRFCOMMConnector();
	AndroidRfComm rfcomm;

signals:
	void signalReceivedMessage( QString a_strAnswer );
	void signalConnectFinished( bool a_bIsConnected );
	void signalDisconnectFinished();
	void signalFinished();
	void signalDuringConnection( bool a_bIsDuringConnection );
public slots:
	void slotSendMessage( const QString a_strMessage );
	bool slotConnect();
	void slotDisconnect();
	void slotProcess();
private slots:
	void slotMonitorAnswer();
private:
	bool CheckIfMyDeviceIsAvailable();

	QTimer m_timerAnswerMonitor;
	QString m_strDeviceAnswer;
};

#endif // CANDROIDRFCOMMCONNECTOR_H
