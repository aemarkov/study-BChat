#ifndef __BASECONTAINER_H__
#define __BASECONTAINER_H__

#include <stdint.h>

namespace Containers
{

	/*!
	 * \brief Базовый класс контейнера
	 *
	 * Контейнер инкапсулирует в себя различные связанные данные,
	 * например, видеопоток, разрешение итп
	 *
	 * Предоставляет методыч
	 */
	class BaseContainer
	{
	public:

		/*!
		 * \brief Возвращает необходимый размер для сериализации
		 */
		virtual uint32_t GetSize() const = 0;

		/*!
		 * \brief Сериализует себя в буфер по указанному указателю
		 *
		 * ВНИМАНИЕ: В буфере должно быть как минимум GetSize() байт
		 */
		virtual void Serialize(uint8_t* buffer) const = 0;

		/*!
		 * \brief Десериализует буфер в себя (уже существующий объект)
		 */
		virtual void Deserialize(const uint8_t* buffer) = 0;
	};

}

#endif
