﻿#ifndef __SIMPLEDELETER_H__
#define __SIMPLEDELETER_H__

/*!
 * \brief Используется для автоматического освобождения ресурсов
 *        при выходе за область видимости
 *
 * Этот класс используется для хранения ресурсов, представляемых простыми
 * типами (дескрипторы, хэндлеры итп), потому что хранимый объект передается по значению.
 *
 * Экземпляры этого класса должны быть локальными\глобальными переменными, но не
 * выделенными в куче, иначе потребуется ручное удаление.
 *
 * Не передавайте эти объекты в функцию по значению, только по ссылке\указателю, потому что
 * при выходе из функции будет вызван деструктор, который освободит ресурс
 */

template <class T>
class SimpleDeleter
{
public:
	
	SimpleDeleter()
	{

	}

	SimpleDeleter(T t)
	{
		this->t = t;
	}

	/*\
	 *\brief получить хранящийся элемент
	 */
	T& operator*()
	{
		return t;
	}

protected:

	T t;

};

#endif
