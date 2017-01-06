#include "cryptoapi.h"

using namespace Crypto;

CryptoAPI::CryptoAPI(const char* containerName):_sessionKeyMutex()
{
	_hCryptProv = nullptr;
	_hSessionKey = nullptr;

	HCRYPTPROV hCryptProv;
	HCRYPTKEY hCryptKey;

	//Получаем провайдер
	if (!CryptAcquireContextA(
		&hCryptProv,
		containerName,			//Имя контейнера
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


		throw CryptoException(std::string("Cryptographic context with container \"")
			+ std::string(containerName)
			+ std::string(+"\" couldn't be accured"));
	}

	_hCryptProv = std::unique_ptr<HCRYPTPROV, HCRYPTPROV_Deleter>(&hCryptProv);
}


CryptoAPI::~CryptoAPI()
{
	CleanUp();
}





///////////////////////////////////////////////////////////////////////////////////////////////////


//Генерирует сессионный ключ
bool CryptoAPI::CreateSessionKey()
{	
	HCRYPTKEY hSessionKey;

	_sessionKeyMutex.lock();
	bool result =  CryptGenKey(*_hCryptProv, CALG_G28147, CRYPT_EXPORTABLE, &hSessionKey);
	_hSessionKey = std::unique_ptr<HCRYPTKEY, HCRYPTKEY_Deleter>(&hSessionKey);
	_sessionKeyMutex.unlock();

	return result;
}


//Экспортирует сессионный ключ и шифрует открытым ключом
//соответствующего пользователя
bool CryptoAPI::ExportSessionKeyForUser(std::string certSerialNumber)
{
	if (_hCryptProv == nullptr)
		throw CryptoException("Crypto provider is not initialized");

	if (_hSessionKey == nullptr)
		throw CryptoException("Session key does not exists");

	//Открываем хранилище сертификатов других пользователей
	HCERTSTORE _hCertStore = OpenCertStore(CERT_OTHERS_STORE);
	std::unique_ptr<HCERTSTORE, HCERTSTORE_Deleter> hOtherStore(&_hCertStore);

	if (*hOtherStore == NULL)
	{
		throw CryptoException("Can't open certificate store");
	}

	//Ищем сертификат получателя
	PCCERT_CONTEXT _certContext = CertFindCertificateInStore(*hOtherStore, _dwCertEncodingType, 0, CERT_FIND_SUBJECT_STR, certSerialNumber.c_str(), NULL);
	std::unique_ptr<PCCERT_CONTEXT, PCCERT_CONTEXT_Deleter> certContext(&_certContext);
	if (certContext == NULL)
	{
		throw CryptoException("User's certificate not found");
	}

	HCRYPTPROV prov = *_hCryptProv;
	
	//Получаем ключ
	HCRYPTKEY  _hPublicKey;
	if (!CryptImportPublicKeyInfo(
		prov,
		_dwCertEncodingType,
		&_certContext->pCertInfo->SubjectPublicKeyInfo,
		&_hPublicKey))
	{
		throw CryptoException("Can't import public key from certificate");
	}
	std::unique_ptr<HCRYPTKEY, HCRYPTKEY_Deleter> hPublicKey(&_hPublicKey);

	//Экспортируем наш сеансовый ключ, шифруя его открытым ключом получателя
	DWORD dwBlobLen;
	BYTE* sessionKeyBlob;

	//Сначала - размер, потом сам ключ
	if (!CryptExportKey(
		*_hSessionKey,
		NULL,
		PLAINTEXTKEYBLOB,
		0,
		NULL,
		&dwBlobLen
	))
	{
		throw CryptoException("Can't export session key");
	}

	//Выделяем память под BLOB сессионного ключа
	sessionKeyBlob = new BYTE[dwBlobLen];

	//Экспортируем сам ключ
	if (!CryptExportKey(
		*_hSessionKey,
		*hPublicKey,
		SIMPLEBLOB,
		0,
		sessionKeyBlob,
		&dwBlobLen
	))
	{
		throw CryptoException("Can't export session key");
	}
}

//Импортирует сессионный ключ, зашифрованный собственным
//(нашим) открытым ключом
bool CryptoAPI::ImportSessionKey(uint8_t* key, uint32_t keySize)
{
	throw NotImplementedException();
}



//Шифрует данные с использованием сессионного ключа
bool CryptoAPI::Encrypt(uint8_t* data, uint32_t size)
{
	throw NotImplementedException();
}

//Расшифровывает данные с использованием сессионного ключа

bool CryptoAPI::Decrypt(uint8_t* data, uint32_t size)
{
	throw NotImplementedException();
}


///////////////////////////////////////////////////////////////////////////////////////////////////

//Закрывает и очищает все дескрипторы
void CryptoAPI::CleanUp()
{

	/*if (_hCryptProv)
	if (!CryptReleaseContext(_hCryptProv, NULL))
	throw new CryptoException("Cant' close crypto provider");*/
}


//Открывает хранилище сертификатов
HCERTSTORE CryptoAPI::OpenCertStore(std::string storeName)
{
	if (_hCryptProv == nullptr)
		throw CryptoException("Crypto provider is not initialized");

	HCERTSTORE hCertStore = CertOpenSystemStoreA(*_hCryptProv, storeName.c_str());
	if (!hCertStore)
	{
		//throw new CryptoException(std::string("Can't open system store \"") + std::string(storeName) + std::string("\""));
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