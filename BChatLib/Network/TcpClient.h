#pragma once
#include "master.h"
#include <new>          // std::bad_alloc
#include "util\Logger\Logger.h"

/*!
 * \brief Обеспечивает двусторонний обмен данными по сети при помощи TCP
 */
class TcpClient
{
public:
	TcpClient(SOCKET socket);	
	TcpClient();
	~TcpClient();	

	SOCKET GetSocket();									// Геттер для сокета
	int Recv(char** message, int* msgLength);			// Получить сообщение
	int SimpleRecv(char* message, int length);			// Более низкоуровенвый прием без встроенной длины сообщения
	int Send(char* message, int messageLength);			// Отправить сообщение
	int SimpleSend(char* message, int messageLength);	// Более низкоуровневая передача без встроенное длины
	int Connect(char* ip, int port);					// Подключиться
	void Close();										// Закрыть сокет

private:
	SOCKET _socket;

	//void setOptions(SOCKET sock);

	int bufferSize = 1000000;

	//void flushSocket();
};

