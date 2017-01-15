#include "SimpleContainerMultiplexor.h"

using namespace Containers;

SimpleContainerMultiplexor::SimpleContainerMultiplexor(uint32_t bufferSize)
{
	_bufferSize = bufferSize;
	_sendBuffer = new uint8_t[bufferSize];
}

SimpleContainerMultiplexor::~SimpleContainerMultiplexor()
{
	delete[] _sendBuffer;
}

void Containers::SimpleContainerMultiplexor::InputVideoContainer(const Containers::VideoFrameContainer * container)
{
	InputContainer(container);
}


void Containers::SimpleContainerMultiplexor::InputChatContainer(const Containers::VideoFrameContainer * container)
{
	InputContainer(container);
}


//Получение данных от какого-то источника
void SimpleContainerMultiplexor::InputContainer(const Containers::BaseContainer* container)
{
	try
	{
		uint32_t size = _headerSize; // +sizeof(userId)
		size += container->GetSize();

		uint8_t * buffer0 = _sendBuffer;

		memcpy(buffer0, _header, _headerSize);
		buffer0 += _headerSize;

		//memcpy(buffer, &userId, sizeof(userId));
		//buffer += sizeof(userId);

		container->Serialize(buffer0);

		emit OutputData(_sendBuffer, size);
	}
	catch (Exception ex)
	{
		//TODO:  Показать диалоговое окно
	}
}


//Получение данных в байтовом виде
void SimpleContainerMultiplexor::InputData(uint8_t * buffer, uint32_t size)
{
	try
	{

		if (buffer == nullptr)
		{
			//throw new Exception("Input data is NULL");
			Logger::Instance()->WriteException("Input data is NULL");
			return;
		}

		//Сравниваем заголовок
		if (memcmp(buffer, _header, _headerSize) != 0)
		{
			//throw new Exception("Input data is invalid, maybe Session Key is invalid");
			Logger::Instance()->WriteException("Input data is invalid, maybe Session Key is invalid");
			return;
		}

		buffer += _headerSize;

		//Читаем Id пользователя
		//memcpy(&userId, buffer, sizeof(userId));
		//buffer += sizeof(userId);

		//TODO: определить тип контейнера...

		//Читаем кадр
		_videoFrameContainer.Deserialize(buffer);
		emit OutputFrame(&_videoFrameContainer);
	}
	catch (Exception ex)
	{
	}
}
