#include "cryptoapi.h"

CryptoAPI::CryptoAPI(const char* containerName):_sessionKeyMutex()
{

	//Получаем провайдер
	if (!CryptAcquireContextA(
		&_hCryptProv,
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
}


CryptoAPI::~CryptoAPI()
{
	CleanUp();
}



//Закрывает и очищает все дескрипторы
void CryptoAPI::CleanUp()
{
	
	if (_hCryptProv)
		if (!CryptReleaseContext(_hCryptProv, NULL))
			throw new CryptoException("Cant' close crypto provider");
}


//.................................................................................................



//Открывает хранилище сертификатов
HCERTSTORE CryptoAPI::OpenCertStore(std::string storeName)
{
	HCERTSTORE hCertStore = CertOpenSystemStoreA(_hCryptProv, storeName.c_str());
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
			throw new CryptoException("Can't close certificate store");

}

//Генерирует сессионный ключ
bool CryptoAPI::CreateSessionKey()
{
	_sessionKeyMutex.lock();
	bool result =  CryptGenKey(_hCryptProv, CALG_G28147, CRYPT_EXPORTABLE, &_hSessionKey);
	_sessionKeyMutex.unlock();

	return result;
}


//Экспортирует сессионный ключ и шифрует открытым ключом
//соответствующего пользователя
bool CryptoAPI::ExportSessionKeyForUser(std::string certSerialNumber)
{
	//Открываем хранилище сертификатов других пользователей
	HCERTSTORE _hCertStore = OpenCertStore(CERT_OTHERS_STORE);
	std::unique_ptr<HCERTSTORE, HCERTSTORE_Deleter> hOtherStore(&_hCertStore);

	if (*hOtherStore == NULL)
	{
		throw new CryptoException("Can't open certificate store");
	}

	//Ищем сертификат
	PCCERT_CONTEXT _certContext = CertFindCertificateInStore(*hOtherStore, _dwCertEncodingType, 0, CERT_FIND_SUBJECT_STR, certSerialNumber.c_str(), NULL);
	std::unique_ptr<PCCERT_CONTEXT, PCCERT_CONTEXT_Deleter> certContext(&_certContext);
	if (certContext == NULL)
	{
		throw new CryptoException("User's certificate not found");
	}

	//Получаем ключ
	HCRYPTKEY  _hPublicKey;
	if (!CryptImportPublicKeyInfo(
		_hCryptProv,
		_dwCertEncodingType,
		&(*certContext)->pCertInfo->SubjectPublicKeyInfo,
		&_hPublicKey))
	{
		throw new CryptoException("Can't import public key from certificate");
	}
	std::unique_ptr<HCRYPTKEY, HCRYPTKEY_Deleter> hPublicKey(&_hPublicKey);

	//Экспортируем наш сеансовый ключ, шифруя его открытым ключом получателя
	DWORD dwBlobLen;

	//Сначала - размер, потом сам ключ
	if (!CryptExportKey(
		_hSessionKey,
		*hPublicKey,
		SIMPLEBLOB,
		0,
		NULL,
		&dwBlobLen
	))
	{
		throw new CryptoException("Can't export session key");
	}

	//CryptDestroyKey(hPublicKey);
	//CertFreeCertificateContext(certContext);
	//CloseCertStore(hOtherStore);
}

//Импортирует сессионный ключ, зашифрованный собственным
//(нашим) открытым ключом
bool CryptoAPI::ImportSessionKey(uint8_t* key, uint32_t keySize)
{
	throw new NotImplementedException();
}



//Шифрует данные с использованием сессионного ключа
bool CryptoAPI::Encrypt(uint8_t* data, uint32_t size)
{
	throw new NotImplementedException();
}

//Расшифровывает данные с использованием сессионного ключа

bool CryptoAPI::Decrypt(uint8_t* data, uint32_t size)
{
	throw new NotImplementedException();
}


//...................... ФУНКЦИИ ЗАКРЫТИЯ ОБЪЕКТОВ WINAPI .........................................

void CryptoAPI::CloseCyrptoProv(HCRYPTPROV* hCryptProv)
{

}

void CryptoAPI::CloseKey(HCRYPTKEY* hKey)
{

}

void CryptoAPI::CloseCertStore(HCERTSTORE* hCertStore)
{

}