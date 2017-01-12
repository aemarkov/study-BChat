#include "cryptoapi.h"

using namespace Crypto;

Crypto::CryptoAPI::CryptoAPI():_sessionKeyMutex()
{
}

CryptoAPI::CryptoAPI(std::string containerName):CryptoAPI()
{
	Init(containerName);
}


CryptoAPI::~CryptoAPI()
{

}

void Crypto::CryptoAPI::Init(std::string containerName)
{

	//Получаем провайдер
	if (!CryptAcquireContextA(
		&*_hCryptProv,
		containerName.c_str(),	//Имя контейнера
		NULL,					//Не указываем провайдера?
		PROV_GOST_2012_256,
		CRYPT_VERIFYCONTEXT
	))
	{
		/*
		Не удалось получить провайдер с заданным именем контейнером
		Самостоятельно создать контейнер можно, но крипто про не сохранит
		его до тех пор, пока в него не будет добавлен ключ или сертификат (???).

		Поэтому надо создать сертификат и установить его в конейнер
		https://www.cryptopro.ru/certsrv/certrqma.asp (тестовый УЦ крипто-про)

		Там можно выбрать "существующий набор ключей" или "новый набор ключей"
		Если новый - то создается контейнер и генерируется новый ключ.

		На контейнер идет один ключ? Или свой на каждый сертификат?

		*/

		//throw CryptoException(QString("Cryptographic context with container \"%1\" couldn't be accured").arg(containerName));
		throw CryptoException("Cryptographic context with container \"%1\" couldn't be accured");
	}

	//Обнуляем параметры. Они должны быть одинаковые при шифровании и расшифровке
	//Размер - BlockSizeBits/8. Для ГОСТ-8147 размер блока наверное 64 бит
	memset(_keyParams, 0, 64 / 8);
}

///////////////////////////////////////////////////////////////////////////////////////////////////


//Генерирует сессионный ключ
bool CryptoAPI::CreateSessionKey()
{	

	_sessionKeyMutex.lock();
	bool result =  CryptGenKey(*_hCryptProv, CALG_G28147, CRYPT_EXPORTABLE, &*_hSessionKey);
	_sessionKeyMutex.unlock();

	return result;
}

//Экспортирует сессионный ключ и шифрует открытым ключом
//соответствующего пользователя
void CryptoAPI::ExportSessionKeyForUser(std::string myCertSubjectString, std::string responderCertSubjectString, uint8_t** publicKeyBlob, uint32_t* blobSize)
{
	HCRYPTPROV_SimpleDeleter hProvSender;
	HCRYPTKEY_SimpleDeleter hAgreeKey;

	CreateAgreeKey(myCertSubjectString, responderCertSubjectString, &*hProvSender, &*hAgreeKey);

	//Экспортируем наш сеансовый ключ, шифруя его ключом согласования (???)
	if (!(ExportKey(*_hSessionKey,	*hAgreeKey, SIMPLEBLOB, publicKeyBlob, (DWORD*)blobSize)))
	{
		throw CryptoException("Can't export session key");
	}
	
}

//Импортирует сессионный ключ, зашифрованный собственным
//(нашим) открытым ключом
void CryptoAPI::ImportSessionKey(uint8_t* key, uint32_t keySize, std::string myCertSubjectString, std::string senderCertSubjectString)
{
	HCRYPTPROV_SimpleDeleter hProv;
	HCRYPTKEY_SimpleDeleter hAgreeKey;

	CreateAgreeKey(myCertSubjectString, senderCertSubjectString, &*hProv, &*hAgreeKey);

	_sessionKeyMutex.lock();

	if (!CryptImportKey(*hProv, key, keySize, *hAgreeKey, 0,&*_hSessionKey))
	{
		_sessionKeyMutex.unlock();
		throw CryptoException("Can't import session key");
	}

	_sessionKeyMutex.unlock();
}

/*!
 * \brief Экспортирует свой сертификат без приватного ключа в формате x509 DER
 */
void Crypto::CryptoAPI::ExportMyCertificate(std::string myCertSubjectString, uint8_t ** certBuffer, uint32_t * bufferLength)
{
	PCCERT_CONTEXT_SimpleDeleter myCert;
	*myCert = FindCertificate(CERT_PERSONAL_STORE, myCertSubjectString);

	*bufferLength = (*myCert)->cbCertEncoded;
	*certBuffer = new uint8_t[*bufferLength];
	memcpy(*certBuffer, (*myCert)->pbCertEncoded, *bufferLength);
}

//Шифрует данные с использованием сессионного ключа
void CryptoAPI::Encrypt(uint8_t* data, uint32_t size)
{
	DWORD dataLen = size;

	if (!CryptSetKeyParam(*_hSessionKey, KP_IV, (const BYTE*)_keyParams, 0))
	{
		DWORD error = GetLastError();
		Util::Logger::Instance()->Write(QString("Can't set key params. Error: %1").arg(error, 0, 16));
		//throw  CryptoException(QString("Can't set key params. Error: %1").arg(error, 0, 16));
		//throw CryptoException("Can't set key params");
	}

	if (!CryptEncrypt(*_hSessionKey, NULL, true, NULL, data, &dataLen, size))
	{
		DWORD error = GetLastError();
		Util::Logger::Instance()->Write(QString("Can't encrypt data. Error: %1").arg(error, 0, 16));
		//throw  CryptoException(QString("Can't encrypt data. Error: %1").arg(error, 0, 16));
		//throw CryptoException("Can't encrypt data");
	}
}

//Расшифровывает данные с использованием сессионного ключа

void CryptoAPI::Decrypt(uint8_t* data, uint32_t size)
{
	DWORD dataLen = size;

	if (!CryptSetKeyParam(*_hSessionKey, KP_IV, (const BYTE*)_keyParams, 0))
	{
		DWORD error = GetLastError();
		Util::Logger::Instance()->Write(QString("Can't set key params. Error: %1").arg(error, 0, 16));
		//throw  CryptoException(QString("Can't set key params. Error: %1").arg(error,0,16));
		//throw CryptoException("Can't set key params");
	}

	if (!CryptDecrypt(*_hSessionKey, NULL, true, NULL, data, &dataLen))
	{
		DWORD error = GetLastError();
		Util::Logger::Instance()->Write(QString("Can't decrypt data. Error: %1").arg(error, 0, 16));
		//throw  CryptoException(QString("Can't decrypt data. Error: %1").arg(error, 0, 16));
		//throw CryptoException("Can't decrypt data.");
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////////


//Открывает хранилище сертификатов
HCERTSTORE CryptoAPI::OpenCertStore(std::string storeName)
{
	/*if (!_hCryptProv.IsValid())
		throw CryptoException("Crypto provider is not initialized");*/

	HCERTSTORE hCertStore = CertOpenSystemStoreA(*_hCryptProv, storeName.c_str());
	if (!hCertStore)
	{
		//throw CryptoException(std::string("Can't open system store \"") + std::string(storeName) + std::string("\""));
		return NULL;
	}

	return hCertStore;
}

//Закрывает хранилище сертификатов
void CryptoAPI::CloseCertStore(HCERTSTORE hCertStore)
{
	if (hCertStore)
		if (!CertCloseStore(hCertStore, CERT_CLOSE_STORE_CHECK_FLAG))
			throw CryptoException("Can't close certificate store");

}


//Получает сертификат из хранилища
PCCERT_CONTEXT Crypto::CryptoAPI::FindCertificate(std::string storeName, std::string certName)
{
	//Открытие личного хранилища сертификатов
	HCERTSTORE_SimpleDeleter hStore;
	*hStore = OpenCertStore(storeName);

	if (*hStore == NULL)
		throw CryptoException("Can't open certificate store");

	PCCERT_CONTEXT hCert;
	hCert = CertFindCertificateInStore(
		*hStore,
		_dwCertEncodingType,
		0,
		CERT_FIND_SUBJECT_STR,
		certName.c_str(),
		NULL
	);

	if (hCert == NULL)
		//throw CryptoException(QString("Certificate \"%1\" not found").arg(certName.c_str()));
		throw CryptoException("Certificate \"%1\" not found");

	return hCert;

}

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
bool CryptoAPI::ExportKey(HCRYPTKEY keyToExport, HCRYPTKEY keyToEncode, DWORD blobType, BYTE** keyBlob, DWORD* keySize)
{
	if (!CryptExportKey(
		keyToExport,
		keyToEncode,
		blobType,
		NULL,
		NULL,
		keySize
	))
		return false;
	
	*keyBlob = new BYTE[*keySize];

	if (!CryptExportKey(
		keyToExport,
		keyToEncode,
		blobType,
		NULL,
		*keyBlob,
		keySize
	))
	{
		*keySize = -1;
		keyBlob = NULL;
		return false;
	}

	return true;
}



/*
Создает ключ согласования

Выполняет практически все операции по подготовке к импорту\экспорту сессионного ключа.
Процедура симметрична:

1. Получит наш сертификат
2. Получить наш CSP
3. Получение дескриптора нашего закрытого ключа

4. Поиск сертификата другого участника (получателя/отправителя)
5. Получение его публичного ключа
6. Экспорт в блоб его публичного ключа

7. Получение ключа согласования из нашего приватного и его публичного ключа

*/

void CryptoAPI::CreateAgreeKey(std::string myCertSubjectString, std::string otherCertSubjectString, HCRYPTPROV* hProv, HCRYPTKEY* hAgreeKey)
{
	

	DWORD dwKeySpecSender;

	//Получаем свой сертификт
	PCCERT_CONTEXT_SimpleDeleter hMyCert;

	*hMyCert = FindCertificate(CERT_PERSONAL_STORE, myCertSubjectString);

	// Получение дескриптора CSP, включая доступ к связанному с ним ключевому
	// контейнеру для контекста сертификата pCertSender.
	if (!CryptAcquireCertificatePrivateKey(
		*hMyCert,
		0,
		NULL,
		hProv,
		&dwKeySpecSender,
		NULL
	))
	{
		throw CryptoException("Can't accuire certificate private key");
	}

	//Получение дескриптора своего закрытого ключа
	HCRYPTKEY_SimpleDeleter hMyPrivateKey;

	if (!CryptGetUserKey(
		*hProv,
		dwKeySpecSender,
		&*hMyPrivateKey
	))
	{
		throw CryptoException("Can't get own private key");
	}

	//Ищем сертификат другой стороны (если мы передаем - получателя, если мы принимаем - отправителя)
	PCCERT_CONTEXT_SimpleDeleter hResponderCert;

	*hResponderCert = FindCertificate(CERT_OTHERS_STORE, otherCertSubjectString);

	//Получаем публичный ключ другой стороны
	HCRYPTKEY_SimpleDeleter hPublicKey;

	if (!CryptImportPublicKeyInfoEx(
		*_hCryptProv,
		_dwCertEncodingType,
		&(*hResponderCert)->pCertInfo->SubjectPublicKeyInfo,
		0,
		0,
		NULL,
		&*hPublicKey))
	{
		throw CryptoException("Can't import public key from certificate");
	}

	//Экспортируем публичный ключ другой стороны
	DWORD dwPublicKeyBlobLen;
	BYTE* publicKeyBlob;

	if (!ExportKey(
		*hPublicKey,
		NULL,
		PUBLICKEYBLOB,
		&publicKeyBlob,
		&dwPublicKeyBlobLen
	))
	{
		throw CryptoException("Can't export other's public key");
	}

	//Получаем ключ согласования
	if (!CryptImportKey(
		*hProv,
		publicKeyBlob,
		dwPublicKeyBlobLen,
		*hMyPrivateKey,
		0,
		hAgreeKey
	))
	{
		delete[] publicKeyBlob;
		throw CryptoException("Can't get agree key");
	}

	delete[] publicKeyBlob;
}




std::string CryptoAPI::ErrorToString(DWORD error)
{
	if (error)
	{
		LPVOID lpMsgBuf;
		DWORD bufLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);
		if (bufLen)
		{
			LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
			std::string result(lpMsgStr, lpMsgStr + bufLen);

			LocalFree(lpMsgBuf);

			return result;
		}
	}
	return std::string();
}