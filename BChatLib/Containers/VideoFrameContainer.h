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
		bool IsBuffer() const;
		void CreateBuffer(const uint32_t size);
		void SetBuffer(const uint8_t* buffer, uint32_t size);
		uint8_t* GetBuffer() const;
		void SetWidth(const uint32_t width);
		uint32_t GetWidth() const;
		void SetHeight(const uint32_t height);
		uint32_t GetHeight() const;
		void SetFormat(const QImage::Format format);
		QImage::Format GetFormat() const;

		//Сериализация
		virtual uint32_t GetSize() const override;
		virtual void Serialize(uint8_t* buffer) const override;
		virtual void Deserialize(const uint8_t* buffer) override;

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
