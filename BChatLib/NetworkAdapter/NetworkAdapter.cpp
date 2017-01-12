#include "NetworkAdapter.h"



NetworkAdapter::NetworkAdapter(TcpClient & tcpClient)
{
	_tcpClient = std::move(tcpClient);
}


NetworkAdapter::~NetworkAdapter()
{
}

NetworkAdapter::NetworkAdapter(NetworkAdapter && other)
{
	_tcpClient = std::move(other._tcpClient);
	other._tcpClient = INVALID_SOCKET;
}

NetworkAdapter & NetworkAdapter::operator=(NetworkAdapter && other)
{
	_tcpClient = std::move(other._tcpClient);
	other._tcpClient = INVALID_SOCKET;
	return *this;
}

void NetworkAdapter::SendSlot(uint8_t* data, uint32_t size)
{

}