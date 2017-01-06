#ifndef __WINAPIDELETERS_H__
#define __WINAPIDELETERS_H__

#include "util\Deleters\SmartPointerDeleter.h"
#include "CryptoExceptions.h"
#include <wincrypt.h>

namespace Crypto
{

	class HCRYPTPROV_Deleter :public SmartPointerDeleter<HCRYPTPROV>
	{
	public:
		virtual void operator()(HCRYPTPROV* pointer)
		{
			if (pointer != NULL && *pointer != NULL)
				if (!CryptReleaseContext(*pointer, NULL))
				{
					//throw "Cant' close crypto provider";
				}

			delete pointer;
		}
	};

	class HCRYPTKEY_Deleter :public SmartPointerDeleter<HCRYPTKEY>
	{
	public:
		virtual void operator()(HCRYPTKEY* pointer)
		{
			if (pointer != NULL && *pointer != NULL)
				if (!CryptDestroyKey(*pointer))
				{
					DWORD err = GetLastError();

					//throw "Cant' destroy key";
				}

			delete pointer;
		}
	};

	class HCERTSTORE_Deleter : public SmartPointerDeleter<HCERTSTORE>
	{
	public:
		virtual void operator()(HCERTSTORE* pointer)
		{
			if (pointer != NULL && *pointer != NULL)
				if (!CertCloseStore(*pointer, CERT_CLOSE_STORE_CHECK_FLAG))
				{
					//throw CryptoException("Can't close certificate store");
				}

			delete pointer;
		}
	};

	class PCCERT_CONTEXT_Deleter : public SmartPointerDeleter<PCCERT_CONTEXT>
	{
	public:
		virtual void operator()(PCCERT_CONTEXT* pointer)
		{
			if (pointer != NULL && *pointer != NULL)
				CertFreeCertificateContext(*pointer);

			delete pointer;
		}
	};

}

#endif
