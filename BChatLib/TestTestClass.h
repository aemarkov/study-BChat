#pragma once

#include <qobject.h>

class TestTestClass //:public QObject
{

//Q_OBJECT
public:
	int Sum(int a, int b)
	{
		return a + b;
	}
};
