#pragma once

#include "BaseContainer.h"
#include "ContainerTypes.h"
#include <qstring.h>

namespace Containers
{
	class ChatMessageContainer : public BaseContainer
	{
	public:

		ChatMessageContainer();

		void SetMessage(QString message);
		QString Get_Message() const;

		virtual ContainersType GetType() const override;
		virtual uint32_t GetSize() const override;
		virtual void Serialize(uint8_t* buffer) const override;
		virtual void Deserialize(const uint8_t* buffer) override;

	private:
		static const ContainersType _containerType = CHAT_MESSAGE_CONTAINER;
		QString _message;
	};
}