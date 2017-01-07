#pragma once
#include "master.h"

/*!
 * \brief Обеспечивает двусторонний обмен данными по сети при помощи TCP
 */
class TcpClient
{
public:
	TcpClient(SOCKET socket);	
	TcpClient();
	~TcpClient();	

	SOCKET GetSocket();								// Геттер для сокета
	int Recv(char** message, int* xyuLength);		// Получить сообщение
	int Send(char* message, int messageLength);		// Отправить сообщение
	int Connect(char* ip, int port);				// Подключиться

private:
	SOCKET _socket;
};

