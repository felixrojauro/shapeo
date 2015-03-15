#ifndef CQMLMAINVIEWFRAME_H
#define CQMLMAINVIEWFRAME_H

#include <QQuickView>
#include <QtQml>

class CQmlMainViewFrame : public QQuickView
{
    Q_OBJECT
public:
    explicit CQmlMainViewFrame(QQuickView *parent = 0);
	~CQmlMainViewFrame();

    void registerCustomQMLTypes();
	void Initialize();

	void keepScreenOn();
	void clearScreenOnFlags();
	bool m_bFirstConnectionAttemptFinished;

};
#endif // CQMLMAINVIEWFRAME_H
