#pragma once
//#include "Network\TcpListener.h"
#include "Network\TcpClient.h"
#include "INetwork.h"

class NetworkAdapter : public INetwork
{
public:
	NetworkAdapter(TcpClient &);
	~NetworkAdapter();
	NetworkAdapter(NetworkAdapter&& other);
	NetworkAdapter& operator=(NetworkAdapter&& other);
	NetworkAdapter(const NetworkAdapter&) = delete;

public slots:
	virtual void SendSlot(uint8_t* data, uint32_t size) override;


private:		
	TcpClient _tcpClient;
};

