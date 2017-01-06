#pragma once
#include "TcpClient.h"
#include "master.h"

class TcpListener
{
public:	
	TcpListener();
	TcpListener(int port);
	TcpListener(char* ip, int port);
	~TcpListener();
	
	int Start();				// Начало работы сервера
	TcpClient AcceptClient();	// Начало приема подключений

private:	
	char*		_ip;			// Ip-адрес сервера, принимающего подключения
	int			_port;			// Порт сервера, принимающего подключения
	SOCKET		_inSocket;		// Сокет, на который приходят новые подключения	
};

