#include "QImageToBytesConverter.h"


QImageToBytesConverter::QImageToBytesConverter()
{
	_buffer = nullptr;
	_bufferSize = 0;
}


QImageToBytesConverter::~QImageToBytesConverter()
{
	if (_buffer != nullptr)
		delete[] _buffer;
}

void QImageToBytesConverter::FrameInput(QImage& image)
{
	uint32_t size = image.byteCount();

	if (_buffer == nullptr)
	{
		_buffer = new uint8_t[size];
		_bufferSize = size;
	}

	if (_bufferSize != size)
		throw new Exception("QImage size is changed");

	memcpy(_buffer, image.constBits(), size);
	
	emit DataOutput(_buffer, _bufferSize);

}