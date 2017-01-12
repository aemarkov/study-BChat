#ifndef __FACTORYMETHOD_H__
#define __FACTORYMETHOD_H__

namespace Util
{
	/*!
	 * \brief Базовый шаблонный фабричный метод
	 */

	template <class T>
	class FactoryMethod
	{
	public:
		virtual T* Create() = 0;
	};

}

#endif
