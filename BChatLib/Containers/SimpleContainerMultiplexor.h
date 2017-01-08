#pragma once

#include <qobject.h>
#include "BaseContainer.h"
#include "VideoFrameContainer.h"

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

	public slots:

		/*
		 * \brief ѕолучение данных от какого-то источника
		 *
		 * (шучу, пока только от вебкамеры)
		 * ¬ообще-то надо родител€ принимать BaseContainer, но слоты-сигналы Qt
		 * не коннект€тс€
		 */
		void InputContainer(const Containers::VideoFrameContainer&);
		
		/*
		 * \brief ѕолучение данных в байтовом виде
		 */
		void InputData(uint8_t*, uint32_t);

	signals:

		/*!
		 * \brief ѕередача сформированного массива байт дальше
		 */
		void OutputData(uint8_t*, uint32_t);

		/*!
		 * \brief ѕередача полученного кадра
		 */
		void OutputFrame(const Containers::VideoFrameContainer&);
	
	private:
		
		static const uint32_t _headerSize = 6; //sizeof не работает почему-то
		const uint8_t _header[_headerSize] = { 0x74, 0x75, 0x15, 0x37, 0xAA, 0xBB };

		//»х может быть под каждого пользовател€ массив
		VideoFrameContainer container;

	};
}
