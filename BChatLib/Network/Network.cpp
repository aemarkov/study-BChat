#include "Network.h"



Network::Network()
{
	WSADATA ws;	
	if (FAILED(WSAStartup(MAKEWORD(1, 1), &ws)))
	{
		// Error...		
	}
}


Network::~Network()
{
	WSACleanup();
}
