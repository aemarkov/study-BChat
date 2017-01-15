#ifndef __VIDEOFRAMECONTAINER_H__
#define __VIDEOFRAMECONTAINER_H__

#include <qimage.h>
#include "BaseContainer.h"
#include "common\Exceptions.h"
#include "ContainerTypes.h"

namespace Containers
{
	class VideoFrameContainer : public BaseContainer
	{
	public:

		VideoFrameContainer();
		~VideoFrameContainer();

		//Сеттеры-геттеры
		void SetBuffer(const uint8_t* buffer, uint32_t size);
		uint8_t* GetBuffer() const;

		void SetWidth(const uint32_t width);
		uint32_t GetWidth() const;

		void SetHeight(const uint32_t height);
		uint32_t GetHeight() const;

		void SetFormat(const QImage::Format format);
		QImage::Format GetFormat() const;

		//Сериализация
		virtual ContainersType GetType() const override;
		virtual uint32_t GetSize() const override;
		virtual void Serialize(uint8_t* buffer) const override;
		virtual void Deserialize(const uint8_t* buffer) override;

	private:

		static const ContainersType _containerType = VIDEO_FRAME_CONTAINER;
		uint8_t* _buffer;
		static const uint32_t _bufferSize = 1000000;
		uint32_t _realDataSize;

		uint32_t _width;
		uint32_t _height;
		QImage::Format _format;

	};
}


#endif
