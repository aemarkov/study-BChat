#include "ChatMessageContainer.h"

using namespace Containers;

Containers::ChatMessageContainer::ChatMessageContainer()
{
}

void Containers::ChatMessageContainer::SetMessage(QString message)
{
	_message = message;
}

ContainersType Containers::ChatMessageContainer::GetType() const
{
	return CHAT_MESSAGE_CONTAINER;
}

uint32_t Containers::ChatMessageContainer::GetSize() const
{
	return _message.length() * sizeof(QChar) + sizeof(uint32_t);
}

void Containers::ChatMessageContainer::Serialize(uint8_t * buffer) const
{
	uint32_t size = _message.length();

	memcpy(buffer, &size, sizeof(size));
	buffer += sizeof(size);

	memcpy(buffer, _message.data(), size * sizeof(QChar));
}

void Containers::ChatMessageContainer::Deserialize(const uint8_t * buffer)
{
	uint32_t size;

	memcpy(&size, buffer, sizeof(size));
	buffer += sizeof(size);

	_message.setUnicode((QChar*)buffer, size);
}
