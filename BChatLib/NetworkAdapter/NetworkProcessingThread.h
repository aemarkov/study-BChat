#pragma once

#include <QObject>
#include <qthread.h>
#include "Network\TcpClient.h"
#include "INetwork.h"

class NetworkProcessingThread : public INetwork
{
	Q_OBJECT

public:
	NetworkProcessingThread(TcpClient client, uint32_t bufferSize, int clientIndex);
	~NetworkProcessingThread();

	void run();

public slots :
	virtual void SendSlot(uint8_t*, uint32_t) override;


private:
	TcpClient _tcpClient;
	int _clientIndex;

	//Выделенный буфер, куда будут приниматься сообщения
	//Чтобы избежать постоянных аллокций
	uint8_t* _buffer;
	uint32_t _bufferSize;
};
