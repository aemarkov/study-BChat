#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <qstring.h>
#include <string>

#include "util\Logger\Logger.h"

using namespace Util;

#define ExceptionString QString//  std::string

class Exception
{
public:
	ExceptionString Message;

	Exception() {}
	Exception(ExceptionString message);
	Exception(uint32_t errorCode) :Exception(QString("Error occured, error code: %1").arg(errorCode)) {}
	Exception(ExceptionString message, uint32_t errorCode) :Exception(QString("%1, error code: %2").arg(message).arg(errorCode)) {}
};

class NotImplementedException:public Exception
{
public:
	NotImplementedException() :Exception() {}
};


class NetworkException : public Exception
{
public:
	uint32_t ErrorCode; //==DWORD

	NetworkException() :Exception(){}
	NetworkException(uint32_t errorCode) :Exception(errorCode){}
	NetworkException(ExceptionString message) :Exception(message) {}
	NetworkException(ExceptionString message, uint32_t errorCode) :Exception(message, errorCode) {}
};

#endif