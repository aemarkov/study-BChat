#include "VideoFrameContainer.h"

using namespace Containers;


Containers::VideoFrameContainer::VideoFrameContainer()
{
	_frameBuffer = nullptr;
	_bufferSize = 0;
}

Containers::VideoFrameContainer::~VideoFrameContainer()
{
	if (_frameBuffer != nullptr)
		delete[] _frameBuffer;
}

////////////////////////////////////////// —≈““≈–€ ////////////////////////////////////////////////

bool Containers::VideoFrameContainer::IsBuffer() const
{
	return _frameBuffer != nullptr;
}

void Containers::VideoFrameContainer::CreateBuffer(const uint32_t size)
{
	_bufferSize = size;
	_frameBuffer = new uint8_t[size];
}

void Containers::VideoFrameContainer::SetBuffer(const uint8_t * buffer, uint32_t size)
{
	if (buffer == nullptr)
		throw new Exception("Buffer is not initialized");

	if (_frameBuffer == nullptr)
	{
		_frameBuffer = new uint8_t[size];
		_bufferSize = size;
	}

	if (size != _bufferSize)
		throw new Exception("Buffer has invalid size");

	memcpy(_frameBuffer, buffer, size);
}

uint8_t * Containers::VideoFrameContainer::GetBuffer() const
{
	return _frameBuffer;
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


//////////////////////////////////////// —≈–»¿À»«¿÷»ﬂ /////////////////////////////////////////////


uint32_t VideoFrameContainer::GetSize() const
{
	if (_frameBuffer == nullptr)
		throw new Exception("Buffer is not initialized");

	return _bufferSize + sizeof(_width) + sizeof(_height) + sizeof(_format) + sizeof(_bufferSize);
}

void VideoFrameContainer::Serialize(uint8_t * buffer) const
{
	if (buffer == nullptr)
		throw new Exception("Buffer is NULL");

	if (_frameBuffer == nullptr)
		throw new Exception("Buffer is not initialized");


	memcpy(buffer, &_width, sizeof(_width));
	buffer += sizeof(_width);

	memcpy(buffer, &_height, sizeof(_height));
	buffer += sizeof(_height);

	memcpy(buffer, &_format, sizeof(_format));
	buffer += sizeof(_format);

	memcpy(buffer, &_bufferSize, sizeof(_bufferSize));
	buffer += sizeof(_bufferSize);

	memcpy(buffer, _frameBuffer, _bufferSize);
}

void Containers::VideoFrameContainer::Deserialize(const uint8_t * buffer)
{
	if (buffer == nullptr)
		throw new Exception("Buffer is NULL");

	uint32_t size;

	memcpy(&_width, buffer, sizeof(_width));
	buffer += sizeof(_width);

	memcpy(&_height, buffer, sizeof(_height));
	buffer += sizeof(_height);

	memcpy(&_format, buffer, sizeof(_format));
	buffer += sizeof(_format);

	memcpy(&size, buffer, sizeof(size));

	if (_frameBuffer == nullptr)
	{
		_frameBuffer = new uint8_t[size];
		_bufferSize = size;
	}

	if (size != _bufferSize)
		throw new Exception("Buffer has invalid size");

	memcpy(_frameBuffer, buffer, _bufferSize);
}

