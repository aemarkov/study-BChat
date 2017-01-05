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
 *
 * Примечание:
 * Для устранения зависимости от Windows API, связанные с ним типы данных не 
 * используются в интерфейсе. В связи с этим, таблица соотв. типов:
 *
 * DWORD - uint32_t
 */

#include <mutex>
#include <memory>

#include <windows.h>
#include <wincrypt.h>
#include <CryptoPro\WinCryptEx.h>

#include "CryptoExceptions.h"
#include "common\Exceptions.h"
#include "WinapiDeleters.h"

class CryptoAPI
{
public:
    CryptoAPI(const char* containerName);
	~CryptoAPI();

	/*!
	 * \brief Генерирует сессионный ключ
	 */
	bool CreateSessionKey();

	/*!
	 * \brief Экспортирует сессионный ключ
	 *
	 * Экспортирует сессионный ключ и шифрует открытым ключом
	 * соответствующего пользователя
	 */
	bool ExportSessionKeyForUser(std::string certSerialNumber);

	/*!
 	 *  \brief Импортирует сессионный ключ
	 * 
	 * Импортирует сессионный ключ, зашифрованный собственным
	 * (нашим) открытым ключом
     */
	bool ImportSessionKey(uint8_t* key, uint32_t keySize);

	
	/*!
	 * \brief Шифрует данные с использованием сессионного ключа
	 */
	bool Encrypt(uint8_t* data, uint32_t size);

	/*!
	 * \brief Расшифровывает данные с использованием сессионного ключа
	 */
	bool Decrypt(uint8_t* data, uint32_t size);


private:

	std::string CERT_PERSONAL_STORE = "MY";
	std::string CERT_OTHERS_STORE = "AddressBook";

	//Криптографические объекты
	HCRYPTPROV _hCryptProv;														//Дескриптор криптопровайдера
	HCRYPTKEY _hSessionKey;														//Дескриптор сессионного ключа
	DWORD _dwCertEncodingType = PKCS_7_ASN_ENCODING | X509_ASN_ENCODING;		//Типы обрабатываемых сертификатов

	//Объекты синхронизации
	std::mutex _sessionKeyMutex;	//Мьютекс для глобальных операций с сессионным ключом

	//................................................................................................

	//Закрывает и очищает все дескрипторы
	void CleanUp();

	//Открывает хранилище сертификатов
	HCERTSTORE OpenCertStore(std::string storeName);

	//Закрывает хранилище сертификатов
	void CloseCertStore(HCERTSTORE hCertStore);


	//....................... ФУНКЦИИ ЗАКРЫТИЯ ОЪЕКТОВ WINAPI ........................................

	static void CloseCyrptoProv(HCRYPTPROV* hCryptProv);
	static void CloseKey(HCRYPTKEY* hKey);
	static void CloseCertStore(HCERTSTORE* hCertStore);

};

#endif // CRYPTOAPI_H
