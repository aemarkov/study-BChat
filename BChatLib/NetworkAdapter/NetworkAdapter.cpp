#include "NetworkAdapter.h"



NetworkAdapter::NetworkAdapter(TcpClient tcpClient)
{
	_tcpClient = tcpClient;
}


NetworkAdapter::~NetworkAdapter()
{
}

void NetworkAdapter::SendSlot(uint8_t* data, uint32_t size)
{

}