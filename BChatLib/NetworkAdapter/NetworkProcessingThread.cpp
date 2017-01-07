#include "NetworkProcessingThread.h"

NetworkProcessingThread::NetworkProcessingThread(TcpClient & tcpClient)
{
	_tcpClient = tcpClient;
}

NetworkProcessingThread::~NetworkProcessingThread()
{
}

void NetworkProcessingThread::run()
{		
	int result;
	do
	{
		char*	receivedData;	// Создать буфер данных
		int		size;			// Размер принятых данных

		// Ожидать прием данных
		result = _tcpClient.Recv(&receivedData, &size);
		
		if (result == 0)
		{
			// Испустить сигнал о том, что данные, дескать, приняты
			emit RecvSignal((uint8_t*)receivedData, size);
		}
		else
		{
			emit ConnectionProblem(result);
			return;
		}

		// TODO: НЕ ЗАБЫТЬ НА ВНЕШНЕМ КОДЕ
		//// Очистить память
		//ZeroMemory(receivedData, size);

	} while (result == 0);
}
