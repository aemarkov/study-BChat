#pragma once
#include <crypto/cryptoapi.h>
#include "ICrypt.h"

namespace Crypto
{

	class CryptoApiAdapter : public ICrypt
	{

	public:
		CryptoApiAdapter(CryptoAPI & cryptoApi);
		~CryptoApiAdapter();

		virtual void DecryptSlot(quint8 * key, quint32 keySize) override;
		virtual void EncryptSlot(quint8 *key, quint32 keySize) override;

	private:
		CryptoAPI & _cryptoAPI;
	};

}