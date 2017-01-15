#include "ContainerToQImageConverter.h"

using namespace Webcam;

void ContainerToQImageConverter::DataInput(const Containers::VideoFrameContainer * container)
{
	QImage frame(container->GetWidth(), container->GetHeight(), container->GetFormat());

	uint32_t frameSize = frame.byteCount();

	uint8_t* frameBuffer = frame.bits();
	memcpy(frameBuffer, container->GetBuffer(), frameSize);

	emit FrameOutput(frame);
}