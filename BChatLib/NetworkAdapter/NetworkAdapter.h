#pragma once
//#include "Network\TcpListener.h"
#include "Network\TcpClient.h"
#include "INetwork.h"

class NetworkAdapter : INetwork
{
public:
	NetworkAdapter(TcpClient);
	~NetworkAdapter();

public slots:
	virtual void SendSlot(uint8_t* data, uint32_t size) override;

private:		
	TcpClient _tcpClient;
};

