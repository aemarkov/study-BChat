#include "CryptoApiAdapter.h"

using namespace Crypto;

CryptoApiAdapter::CryptoApiAdapter(CryptoAPI & cryptoApi) : _cryptoAPI(cryptoApi)
{
	
}

CryptoApiAdapter::~CryptoApiAdapter()
{
}

void CryptoApiAdapter::DecryptSlot(uint8_t * data, uint32_t size)
{
	_cryptoAPI.Decrypt(data, size);	
	emit DecryptSignal(data, size);
}

void CryptoApiAdapter::EncryptSlot(uint8_t *data, uint32_t size)
{
	_cryptoAPI.Encrypt(data, size);
	emit EncryptSignal(data, size);
}
