#include "NetworkProcessingThread.h"

NetworkProcessingThread::NetworkProcessingThread(TcpClient tcpClient,  uint32_t bufferSize, int clientIndex)
{
	_tcpClient = tcpClient;
	_bufferSize = bufferSize;
	_buffer = new uint8_t[bufferSize];
	_clientIndex = clientIndex;
}

/*
При ошибки и приема, и передачи надо
все это грохнуть и закрыть

*/

NetworkProcessingThread::~NetworkProcessingThread()
{
	_tcpClient.Close();

	if (_buffer != nullptr)
	{
		delete[] _buffer;
		_buffer = nullptr;
	}

	while (this->isRunning());
}

void NetworkProcessingThread::Stop()
{
	
}


void NetworkProcessingThread::SendSlot(quint8* data, quint32 size)
{
	try
	{
		_tcpClient.Send(data, size);
	}
	catch (NetworkException ex)
	{
		emit ConnectionProblem(ex.ErrorCode, _clientIndex);
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

			// Испустить сигнал о том, что данные, дескать, приняты
			emit RecvSignal((quint8*)_buffer, (quint32)actualLength);
		}
		catch (NetworkException ex)
		{
			//Это очень неприятная ситуация
			//Когда отключаюсь, объект уничтожается, а сокет закрывается.
			//Но потом все-равно срабатывает этот метод и emit вызывает ошибку
			if(ex.ErrorCode!=-1)
				emit ConnectionProblem(ex.ErrorCode, _clientIndex);

			return;
		}
	}
	while (true);
}
