#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <qstring.h>

class Exception
{
public:
	QString Message;

	Exception() {}
	Exception(QString message)
	{
		Message = message;
	}
};

class NotImplementedException:public Exception
{
public:
	NotImplementedException() :Exception() {}
};

#endif