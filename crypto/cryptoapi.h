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
#include <qstring.h>

#include "CryptoExceptions.h"
#include "common\Exceptions.h"
#include "WinapiSimpleDeleters.h"
#include <winerror.h>

namespace Crypto
{

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
		bool ExportSessionKeyForUser(std::string myCertSubjectString, std::string responderCertSubjectString);

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
		HCRYPTPROV_SimpleDeleter _hCryptProv;										//Дескриптор криптопровайдера
		HCRYPTKEY_SimpleDeleter _hSessionKey;										//Дескриптор сессионного ключа

		DWORD _dwCertEncodingType = PKCS_7_ASN_ENCODING | X509_ASN_ENCODING;		//Типы обрабатываемых сертификатов

		//Объекты синхронизации
		std::mutex _sessionKeyMutex;	//Мьютекс для глобальных операций с сессионным ключом

		//................................................................................................

		//Открывает хранилище сертификатов
		HCERTSTORE OpenCertStore(std::string storeName);

		//Закрывает хранилище сертификатов
		void CloseCertStore(HCERTSTORE hCertStore);

		//Получает сертификат из хранилища
		PCCERT_CONTEXT FindCertificate(std::string storeName, std::string certName);

		/*!
		 * \brief Экспортирует ключ
		 * 
		 * param[in] keyToExport ключ, который экспортируется
		 * param[in] keyToEncode ключ, используемый для шифрования ключа (или NULL)
		 * param[in] blobType    тип блоба для экспорта
		 * param[out] keyBlob    буфер с ключем
		 * param[out] keySize    размер буфера
		 *
		 * \return успех операции
		 */
		bool ExportKey(HCRYPTKEY keyToExport, HCRYPTKEY keyToEncode, DWORD blobType, BYTE** keyBlob, DWORD* keySize);

		//Получает текстовое представление ошибки
		std::string ErrorToString(DWORD error);
	};

}

#endif // CRYPTOAPI_H
