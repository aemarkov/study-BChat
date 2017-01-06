#ifndef CRYPTOAPI_H
#define CRYPTOAPI_H

/*!
 * \brief Реализует работу с криптографией средставами Windows Crypto API
 *
 * Позволяет выполнять следующие задачи:
 *  - управление контейнерами
 *  - создание сертификата
 *  - установка сертификатов других пользователей
 *  - генерация сеансового ключа
 *  - шифрование данных
 *  - расшировка данных
 */

#include <windows.h>
#include <wincrypt.h>

class CryptoAPI
{
public:
    CryptoAPI();
};

#endif // CRYPTOAPI_H
