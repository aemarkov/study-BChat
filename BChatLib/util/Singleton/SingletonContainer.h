#ifndef __SINGLETONCONTAINER_H__
#define __SINGLETONCONTAINER_H__

#include "Singleton.h"

/*!
 * \brief Синглтон-контейнер может хранить произвольный не-синглтон
          класс и возвращаеть его по Instance(), вместо собственного
		  instance

	Использование:

	Допустим, существует несколько классов, которые реализуют интерфейс
	или наследуют какой-то класс и должны быть синглтоном.
	При этом вы хотите легко менять эти классы один на другой. 

 */
template<class T>
class SingletonContainer : private Singleton
{
public:

	T&& Inner()
	{
		return SingletonContainer::Instance()->_innerObject;
	}

protected:

	T _innerObject;
};

#endif
