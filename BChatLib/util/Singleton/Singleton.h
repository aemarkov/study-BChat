#ifndef __SINGLETON_H__
#define __SINGLETON_H__

/*!
 * \brief шаблонный базовый класс синглтона, чтобы делать другие синглтоны
 */
class Singleton
{
public:

	/*!
	 * \brief возвращает объект синглтона
	 */
	static Singleton* Instance();

protected:
	Singleton();
	~Singleton();
	Singleton(const Singleton& other) = delete;
	Singleton& operator=(Singleton& other) = delete;

	static Singleton* _instance;
};

#endif