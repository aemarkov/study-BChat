#include "QImageToContainerConverter.h"

using namespace Webcam;

QImageToContainerConverter::QImageToContainerConverter()
{
}


QImageToContainerConverter::~QImageToContainerConverter()
{
}

void QImageToContainerConverter::FrameInput(QImage& image)
{
	uint32_t size = image.byteCount();
	const uint8_t* buffer = image.constBits();
	
	_container.SetBuffer(buffer, size);
	_container.SetWidth(image.width());
	_container.SetHeight(image.height());
	_container.SetFormat(image.format());

	emit DataOutput(&_container);

}