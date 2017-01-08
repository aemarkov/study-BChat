#include "TcpClient.h"

TcpClient::TcpClient(SOCKET socket)
{
	_socket = socket;
}

TcpClient::~TcpClient()
{	
}

TcpClient::TcpClient()
{
}

void TcpClient::Close()
{
	closesocket(_socket);
}

SOCKET TcpClient::GetSocket()
{
	return _socket;
}

int TcpClient::Recv(char** message, int* msgLength)
{	
	int messageLength;
	int actual_len = 0;

	if (SOCKET_ERROR == (actual_len = recv(_socket, (char*)&messageLength, sizeof(int), 0)))
	{
		return WSAGetLastError();		
	}	

	*message = new char[messageLength];
	if (SOCKET_ERROR == (actual_len = recv(_socket, *message, messageLength, 0)))
	{
		return WSAGetLastError();				
	}		
	*msgLength = actual_len;
	return 0;
}


int TcpClient::SimpleRecv(char * message, int length)
{
	int actual_len = 0;
	if (SOCKET_ERROR == (actual_len = recv(_socket, message, length, 0)))
		return WSAGetLastError();
	
	return 0;
}

int TcpClient::Send(char* message, int messageLength)
{
	
	if (SOCKET_ERROR == (send(_socket, (char*)&messageLength, sizeof(int), 0)))
	{
		return WSAGetLastError();
	}
	if (SOCKET_ERROR == (send(_socket, message, messageLength, 0)))
	{
		return WSAGetLastError();
	}
	return 0;
}

int TcpClient::SimpleSend(char * message, int messageLength)
{
	if (SOCKET_ERROR == (send(_socket, message, messageLength, 0)))
	{
		return WSAGetLastError();
	}

	return 0;
}

int TcpClient::Connect(char* ip, int port)
{	
	// Объявим переменную для хранения адреса 
	sockaddr_in s_address;
	// Заполним ее:
	ZeroMemory(&s_address, sizeof(s_address));
	// тип адреса (TCP/IP)
	s_address.sin_family = AF_INET;
	// адрес сервера. Т.к. TCP/IP представляет адреса в числовом виде, то для перевода 
	// адреса используем функцию inet_addr.	
	s_address.sin_addr.S_un.S_addr = inet_addr(ip);
	// Порт. Используем функцию htons для перевода номера порта из обычного в //TCP/IP представление.
	s_address.sin_port = htons(port);
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	// Дальше выполняем соединение:
	if (SOCKET_ERROR == (connect(_socket, (sockaddr *)&s_address, sizeof(s_address))))
	{
		// Error...
		return ERROR;		
	}
	return 0;
}
