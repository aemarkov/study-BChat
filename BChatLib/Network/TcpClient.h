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
	int Recv(char** message, int* msgLength);		// Получить сообщение
	int Send(char* message, int messageLength);		// Отправить сообщение
	int Connect(char* ip, int port);				// Подключиться
	void Close();									// Закрыть сокет

private:
	SOCKET _socket;
};

