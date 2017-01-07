#pragma once

#include <QObject>
#include <qthread.h>
#include "Network\TcpClient.h"

class NetworkProcessingThread : public QThread
{
	Q_OBJECT

public:
	NetworkProcessingThread(TcpClient&);
	~NetworkProcessingThread();

	void run();

signals: 
	void RecvSignal(uint8_t* data, uint32_t size);
	void ConnectionProblem(int errorCode);

private:
	TcpClient _tcpClient;
};
