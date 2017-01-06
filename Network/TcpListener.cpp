#include "TcpListener.h"

TcpListener::TcpListener()
{
}

TcpListener::TcpListener(char* ip, int port)
{
	_ip = ip;
	_port = port;
}

TcpListener::TcpListener(int port)
{
	_port = port;
}

TcpListener::~TcpListener()
{
	closesocket(_inSocket);	
}

int TcpListener::Start()
{
	// Инициализировать сокеты
	// Создать сокет
	sockaddr_in sockInfo;
	ZeroMemory(&sockInfo, sizeof(sockInfo));
	sockInfo.sin_family = AF_INET;	
	sockInfo.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	sockInfo.sin_port = htons(_port);

	_inSocket = socket(AF_INET, SOCK_STREAM, 0);

	int result = bind(_inSocket, (sockaddr*)&sockInfo, sizeof(sockInfo));
	if (result == SOCKET_ERROR)
	{
		return E_FAIL;
	}
	else
	{
		// Установить в режим listen
		bool fail = FAILED(listen(_inSocket, 10));
		if (fail) // Максимум 10 входящих соединений
		{
			return E_FAIL;
		}
		else
		{
			return 0;
		}
	}	
}

TcpClient TcpListener::AcceptClient()
{	
	SOCKET new_sock;
	sockaddr_in new_ca;
	int new_len = sizeof(new_ca);
	ZeroMemory(&new_ca, sizeof(new_ca));
	new_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (FAILED(new_sock = accept(_inSocket, (sockaddr*)&new_ca, &new_len)))
	{
		// Error
	}
	return TcpClient(new_sock);
}
