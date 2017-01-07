#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

//#include <qstring.h>
#include <string>

#define ExceptionString std::string
//#define ExceptionString QString

class Exception
{
public:
	ExceptionString Message;

	Exception() {}
	Exception(ExceptionString message)
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