#include "Exceptions.h"

Exception::Exception(ExceptionString message)
{
	Message = message;
	Logger::Instance()->WriteException(message);
}
