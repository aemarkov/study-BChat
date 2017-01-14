#pragma once

#include <QThread>

class INetwork : public QThread
{
	Q_OBJECT

public:

public slots :
	virtual void SendSlot(uint8_t*, uint32_t) = 0;
	virtual void Stop() = 0;

signals:
	void RecvSignal(uint8_t*, uint32_t);	
	void ConnectionProblem(int, int);
};
