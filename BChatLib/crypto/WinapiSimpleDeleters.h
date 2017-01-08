#ifndef __WINAPISIMPLEDELETERS_H__
#define __WINAPISIMPLEDELETERS_H__

#include "util\Deleters\SimpleDeleter.h"
#include "CryptoExceptions.h"
#include <wincrypt.h>

namespace Crypto
{

	class HCRYPTPROV_SimpleDeleter :public SimpleDeleter<HCRYPTPROV>
	{
	public:
		virtual ~HCRYPTPROV_SimpleDeleter()
		{
			if (!CryptReleaseContext(t, NULL))
			{
				//throw "Cant' close crypto provider";
			}
		}
	};

	class HCRYPTKEY_SimpleDeleter :public SimpleDeleter<HCRYPTKEY>
	{
	public:
		virtual ~HCRYPTKEY_SimpleDeleter()
		{
			if (t == NULL)
				return;

			if (!CryptDestroyKey(t))
			{
				DWORD err = GetLastError();

				//throw "Cant' destroy key";
			}
		}
	};

	class HCERTSTORE_SimpleDeleter : public SimpleDeleter<HCERTSTORE>
	{
	public:
		virtual ~HCERTSTORE_SimpleDeleter()
		{
			if (!CertCloseStore(t, CERT_CLOSE_STORE_CHECK_FLAG))
			{
				//throw CryptoException("Can't close certificate store");
			}
		}

	};

	//“.к. PCCERT_CONTEXT - укзаатель, то если мы попробуем удалиить до инициализации,
	//будет беда. я не смог сделать универсальный метод, чтобы определ€ть 
	//инициаилизировано\не инициалзировано у любых классов, поэтому костыль
	//хм... да оно и так работает. Ќу ладно, пусть будет
	class PCCERT_CONTEXT_SimpleDeleter : public PointerSimpleDeleter<PCCERT_CONTEXT>
	{
	public:
		virtual ~PCCERT_CONTEXT_SimpleDeleter()
		{
			if (t == NULL) return;

			if (!CertFreeCertificateContext(t))
			{
				//Do something
			}
		}
	};

}

#endif