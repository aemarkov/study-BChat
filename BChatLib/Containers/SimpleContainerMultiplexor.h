#pragma once

#include <qobject.h>
#include "BaseContainer.h"
#include "VideoFrameContainer.h"
#include "ChatMessageContainer.h"

namespace Containers
{
	/*!
	 * \brief –азбивает вход€щее сообщание на отдельные контейнеры разных типов
	          и конструирует из исход€щий контейнеров сообщение
		
		ќно должно поддерживать разные типы контейнеров, несколько пользователей,
		и прочее и прочее... Ќо это будет реализовано потом

	 */
	class SimpleContainerMultiplexor : public QObject
	{
		Q_OBJECT

	public:
		SimpleContainerMultiplexor(uint32_t bufferSize);
		~SimpleContainerMultiplexor();

	public slots:

		/*
		 * \brief ѕолучение данных от какого-то источника
		 *
		 * (шучу, пока только от вебкамеры)
		 * ¬ообще-то надо родител€ принимать BaseContainer, но слоты-сигналы Qt
		 * не коннект€тс€
		 */
		void InputVideoContainer(const Containers::VideoFrameContainer*);
		void InputChatContainer(const Containers::ChatMessageContainer*);
	

		/*
		 * \brief ѕолучение данных в байтовом виде
		 */
		void InputData(quint8*, quint32);

	signals:

		/*!
		 * \brief ѕередача сформированного массива байт дальше
		 */
		void OutputData(quint8*, quint32);

		/*!
		 * \brief ѕередача полученного кадра
		 */
		void OutputFrame(const Containers::VideoFrameContainer*);

		/*!
		 * \brief ѕередача полученного сообщени€ в чат
		 */
		void OutputMessage(const Containers::ChatMessageContainer*);
	
	private:
		
		static const uint32_t _headerSize = 6; //sizeof не работает почему-то
		const uint8_t _header[_headerSize] = { 0x74, 0x75, 0x15, 0x37, 0xAA, 0xBB };

		//»х может быть под каждого пользовател€ массив
		VideoFrameContainer _videoFrameContainer;
		ChatMessageContainer _chatMessageContainer;

		uint8_t* _sendBuffer;
		uint32_t _bufferSize;

		void InputContainer(const Containers::BaseContainer*);

	};
}
