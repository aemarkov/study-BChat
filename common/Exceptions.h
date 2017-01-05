#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <string>

class Exception
{
public:
	std::string Message;

	Exception() {}
	Exception(std::string message)
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