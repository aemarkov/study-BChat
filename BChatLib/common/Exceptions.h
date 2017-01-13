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
	NetworkException(uint32_t errorCode) :Exception(QString("Network error occured, error code: %1").arg(errorCode)){}
	NetworkException(ExceptionString message) :Exception(message) {}
	NetworkException(ExceptionString message, uint32_t errorCode) :Exception(QString("%1, error code: %2").arg(message, QString::number(ErrorCode))) {}
};

#endif