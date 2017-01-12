#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

//#include <qstring.h>
#include <string>

#include "util\Logger\Logger.h"
using namespace Util;

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
		Logger::Instance()->WriteException(message.c_str());
	}
};

class NotImplementedException:public Exception
{
public:
	NotImplementedException() :Exception() {}
};

#endif