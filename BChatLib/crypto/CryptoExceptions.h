#ifndef __CRYPTOEXCEPTIONS_H__
#define __CRYPTOEXCEPTIONS_H__

//#include <qstring.h>
#include <string>
#include "common\Exceptions.h"

namespace Crypto
{

	/*!
	 * \brief Базовый тип исключения криптографических функций
	 */
	class CryptoException :public Exception
	{
	public:

		CryptoException() :Exception() {}
		CryptoException(uint32_t errorCode) :Exception(errorCode) {}
		CryptoException(ExceptionString message) :Exception(message) {}
		CryptoException(ExceptionString message, uint32_t errorCode) :Exception(message, errorCode) {}
	};
}

#endif