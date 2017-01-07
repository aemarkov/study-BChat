#include "CppUnitTest.h"
#include "TestTestClass.h"

#include "util\Singleton\SingletonContainer.h"
#include "util\FactoryMethod\FactoryMethod.h"
#include "Logger\Logger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Util;

//Интерфейс
class ITestInterface
{
public:
	virtual int Method() = 0;
};



//Одна реализация
class TestA : public ITestInterface
{
public:
	virtual int Method() override
	{
		return 1;
	}
};

//Другая реализация
class TestB : public ITestInterface
{
public:
	virtual int Method() override
	{
		return 2;
	}
};




//Создатель первой реализации
class TestACreator:FactoryMethod<TestA>
{
public:
	virtual TestA* Create() override
	{
		return new TestA();
	}
};

//Создатель второой реализации
class TestBCreator :FactoryMethod<TestB>
{
public:
	virtual TestB* Create() override
	{
		return new TestB();
	}
};




//Синглтон первой реализации
class TestASingletonContainer : public SingletonContainer<ITestInterface, TestACreator>
{

};

//Синглтон второй реализации
class TestBSingletonContainer : public SingletonContainer<ITestInterface, TestBCreator>
{
};


TEST_CLASS(SingletonContainer_tests)
{
public:

	TEST_METHOD(SingletonContainer_Inner)
	{
	 	int a = TestASingletonContainer::Inner()->Method();
		int b = TestBSingletonContainer::Inner()->Method();

		Assert::AreEqual(a, 1);
		Assert::AreEqual(b, 2);
	}

};
