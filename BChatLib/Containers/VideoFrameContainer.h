#ifndef __VIDEOFRAMECONTAINER_H__
#define __VIDEOFRAMECONTAINER_H__

#include <qimage.h>
#include "BaseContainer.h"
#include "common\Exceptions.h"

namespace Containers
{
	class VideoFrameContainer : BaseContainer
	{
	public:

		VideoFrameContainer();
		VideoFrameContainer(uint32_t userId);
		~VideoFrameContainer();

		//Сеттеры
		bool IsBuffer();
		void CreateBuffer(uint32_t size);
		void SetBuffer(uint8_t* buffer, uint32_t size);
		void SetWidth(uint32_t width);
		void SetHeight(uint32_t height);
		void SetFormat(QImage::Format format);

		//Сериализация
		virtual uint32_t GetSize() override;
		virtual void Serialize(uint8_t* buffer) override;
		virtual void Deserialize(uint8_t* buffer) override;

	private:

		uint8_t* _frameBuffer;
		uint32_t _bufferSize;

		uint32_t _userId;
		uint32_t _width;
		uint32_t _height;
		QImage::Format _format;

	};
}


#endif
