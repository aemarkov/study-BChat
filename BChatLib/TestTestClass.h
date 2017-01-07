#pragma once

#include <qobject.h>
#include <qstring.h>

class TestTestClass //:public QObject
{

//Q_OBJECT
public:
	bool Sum(QString a, QString b)
	{
		return a == b;
	}
};
