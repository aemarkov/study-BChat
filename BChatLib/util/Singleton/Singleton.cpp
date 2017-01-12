#include "Singleton.h"

using namespace Util;

Singleton* Singleton::_instance = nullptr;

//возвращает объект синглтона
Singleton * Singleton::Instance()
{
if (!_instance)
_instance = new Singleton();

return _instance;
}


Singleton::Singleton()
{
}

Singleton::~Singleton()
{
}