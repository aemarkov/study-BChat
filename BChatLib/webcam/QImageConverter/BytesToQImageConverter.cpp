#include "BytesToQImageConverter.h"


void BytesToQImageConverter::DataInput(uint8_t* data, uint32_t size)
{
	//TODO: получать разрешение от клиента
	int width = 640;
	int height = 480;

	QImage frame(640, 480, QImage::Format::Format_RGB16);

	int frameSize = frame.byteCount();

	uint8_t* frameBuffer = frame.bits();
	memcpy(frameBuffer, data, size);

	emit FrameOutput(frame);
}