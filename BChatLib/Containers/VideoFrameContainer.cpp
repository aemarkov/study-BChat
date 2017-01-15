#include "VideoFrameContainer.h"

using namespace Containers;


Containers::VideoFrameContainer::VideoFrameContainer()
{
	_buffer = new uint8_t[_bufferSize];
}

Containers::VideoFrameContainer::~VideoFrameContainer()
{
	if (_buffer != nullptr)
		delete[] _buffer;
}

////////////////////////////////////////// ÑÅÒÒÅÐÛ ////////////////////////////////////////////////

void Containers::VideoFrameContainer::SetBuffer(const uint8_t * buffer, uint32_t size)
{
	if (buffer == nullptr)
	{
		Logger::Instance()->WriteException("VideFrameContainer: Buffer is not initialized");
		return;
	}

	if (size > _bufferSize)
	{
		Logger::Instance()->WriteException(QString("Video frame container buffer size is %1, but input data size is %2").arg(_bufferSize).arg(size));
		return;
	}

	_realDataSize = size;
	memcpy(_buffer, buffer, size);
}

uint8_t * Containers::VideoFrameContainer::GetBuffer() const
{
	return _buffer;
}

void Containers::VideoFrameContainer::SetWidth(const uint32_t width)
{
	_width = width;
}

uint32_t Containers::VideoFrameContainer::GetWidth() const
{
	return _width;
}

void Containers::VideoFrameContainer::SetHeight(const uint32_t height)
{
	_height = height;
}

uint32_t Containers::VideoFrameContainer::GetHeight() const
{
	return _height;
}

void Containers::VideoFrameContainer::SetFormat(const QImage::Format format)
{
	_format = format;
}

QImage::Format Containers::VideoFrameContainer::GetFormat() const
{
	return _format;
}


//////////////////////////////////////// ÑÅÐÈÀËÈÇÀÖÈß /////////////////////////////////////////////


ContainersType Containers::VideoFrameContainer::GetType() const
{
	return _containerType;
}

uint32_t VideoFrameContainer::GetSize() const
{
	return _realDataSize + sizeof(_width) + sizeof(_height) + sizeof(_format) + sizeof(_realDataSize) + sizeof (_containerType);
}

void VideoFrameContainer::Serialize(uint8_t * buffer) const
{
	if (buffer == nullptr)
	{
		Logger::Instance()->WriteException("VideFrameContainer: Buffer is null");
		return;
	}

	memcpy(buffer, &_containerType, sizeof(_containerType));
	buffer += sizeof(_containerType);

	memcpy(buffer, &_width, sizeof(_width));
	buffer += sizeof(_width);

	memcpy(buffer, &_height, sizeof(_height));
	buffer += sizeof(_height);

	memcpy(buffer, &_format, sizeof(_format));
	buffer += sizeof(_format);

	memcpy(buffer, &_realDataSize, sizeof(_realDataSize));
	buffer += sizeof(_realDataSize);

	memcpy(buffer, _buffer, _realDataSize);
}

void Containers::VideoFrameContainer::Deserialize(const uint8_t * buffer)
{
	if (buffer == nullptr)
	{
		Logger::Instance()->WriteException("VideFrameContainer: Buffer is NULL");
		return;
	}

	uint32_t size;

	memcpy(&_width, buffer, sizeof(_width));
	buffer += sizeof(_width);

	memcpy(&_height, buffer, sizeof(_height));
	buffer += sizeof(_height);

	memcpy(&_format, buffer, sizeof(_format));
	buffer += sizeof(_format);

	memcpy(&size, buffer, sizeof(size));
	buffer += sizeof(size);

	if(size>_bufferSize)
		throw new Exception(QString("Video frame container buffer size is %1, but input data size is %2").arg(_bufferSize).arg(size));

	_realDataSize = size;
	memcpy(_buffer, buffer, size);
}

