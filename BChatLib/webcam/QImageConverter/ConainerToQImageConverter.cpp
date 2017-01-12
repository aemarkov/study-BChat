#include "ContainerToQImageConverter.h"

using namespace Webcam;

void ContainerToQImageConverter::DataInput(const Containers::VideoFrameContainer * container)
{
	QImage frame(container->GetWidth(), container->GetHeight(), container->GetFormat());

	int frameSize = frame.byteCount();

	uint8_t* frameBuffer = frame.bits();
	memcpy(frameBuffer, container->GetBuffer(), container->GetSize());

	emit FrameOutput(frame);
}