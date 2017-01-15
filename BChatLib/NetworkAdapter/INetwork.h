#pragma once

#include <QThread>

class INetwork : public QThread
{
	Q_OBJECT

public:

public slots :
	virtual void SendSlot(quint8*, quint32) = 0;
	virtual void Stop() = 0;

signals:
	void RecvSignal(quint8*, quint32);	
	void ConnectionProblem(int, int);
};
