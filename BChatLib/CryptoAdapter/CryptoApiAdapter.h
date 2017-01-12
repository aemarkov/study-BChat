#pragma once
#include <crypto/cryptoapi.h>
#include "ICrypt.h"
using namespace Crypto;

class CryptoApiAdapter : public ICrypt
{	

public:
	CryptoApiAdapter(CryptoAPI & cryptoApi);
	~CryptoApiAdapter();
	
	virtual void DecryptSlot(uint8_t * key, uint32_t keySize) override;
	virtual void EncryptSlot(uint8_t *key, uint32_t keySize) override;

private:
	CryptoAPI & _cryptoAPI;
};
