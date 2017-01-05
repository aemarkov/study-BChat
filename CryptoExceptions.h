#ifndef __CRYPTOEXCEPTIONS_H__
#define __CRYPTOEXCEPTIONS_H__

#include <string>
#include "common\Exceptions.h"

/*!
 * \brief Базовый тип исключения криптографических функций
 */
class CryptoException:public Exception
{
public:
	
	CryptoException():Exception() {}
	CryptoException(std::string message) :Exception(message) {}
};

#endif