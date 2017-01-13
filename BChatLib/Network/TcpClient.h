#pragma once
#include "master.h"
#include <new>          // std::bad_alloc
#include "util\Logger\Logger.h"
#include <qdebug.h>

/*!
 * \brief Обеспечивает двусторонний обмен данными по сети при помощи TCP
 */
class TcpClient
{
public:
	TcpClient(SOCKET socket);	
	TcpClient();
	~TcpClient();	

	// Геттер для сокета
	SOCKET GetSocket();

	/*!
	 * \brief Получить сообщение и его длину
	 * 
	 *  Этот метод использует существующий буфер, вместо аллокации нового
	 * 
	 * \param[in] message - указаетль на буфер, куда будет записаны данные
	 * \param[out] msgLength - указатель на переменную, куда будет записана длина принятых данных
	 * \param[un] bufferSize - размер буфера
	 */
	int Recv(uint8_t* message, uint32_t* msgLength, uint32_t bufferSize);

	/*!
	* \brief Получить сообщение и его длину
	*
	*  Этот метод ВЫДЕЛЯЕТ НОВЫЙ БУФЕР
	*
	* \param[in] message - указаетль на буфер, куда будет записаны данные
	* \param[out] msgLength - указатель на переменную, куда будет записана длина принятых данных
	*/
	int RecvAlloc(uint8_t** message, uint32_t* msgLength);

	// Получить сообщение заданной длины
	int SimpleRecv(uint8_t* message, uint32_t length);


	// Отправить сообщение
	int Send(uint8_t* message, uint32_t messageLength);

	//Отправляет сообщение вместе с его длиной
	int SendWithLength(uint8_t* message, uint32_t messageLength);

	// Подключиться
	int Connect(char* ip, int port);

	// Закрыть сокет
	void Close();

private:
	SOCKET _socket;
};

