#include "NetworkProcessingThread.h"

NetworkProcessingThread::NetworkProcessingThread(TcpClient tcpClient,  uint32_t bufferSize)
{
	_tcpClient = tcpClient;
	_bufferSize = bufferSize;
	_buffer = new uint8_t[bufferSize];
}

/*
При ошибки и приема, и передачи надо
все это грохнуть и закрыть

*/

NetworkProcessingThread::~NetworkProcessingThread()
{
	if (_buffer != nullptr)
	{
		delete[] _buffer;
		_buffer = nullptr;
	}
}

void NetworkProcessingThread::SendSlot(uint8_t* data, uint32_t size)
{
	try
	{
		_tcpClient.Send(data, size);
	}
	catch (NetworkException ex)
	{
		emit ConnectionProblem(ex.ErrorCode);
	}
}

void NetworkProcessingThread::run()
{		
	int result;
	uint32_t		actualLength;			// Размер принятых данных

	do
	{
		try
		{
			// Ожидать прием данных
			_tcpClient.Recv(_buffer, &actualLength, _bufferSize);
		}
		catch (NetworkException ex)
		{
			emit ConnectionProblem(ex.ErrorCode);
			return;
		}

		// Испустить сигнал о том, что данные, дескать, приняты
		emit RecvSignal(_buffer, actualLength);
	}
	while (true);
}
