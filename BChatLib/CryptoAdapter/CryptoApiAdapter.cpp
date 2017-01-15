#include "CryptoApiAdapter.h"

using namespace Crypto;

CryptoApiAdapter::CryptoApiAdapter(CryptoAPI & cryptoApi) : _cryptoAPI(cryptoApi)
{
	
}

CryptoApiAdapter::~CryptoApiAdapter()
{
}

void CryptoApiAdapter::DecryptSlot(quint8 * data, quint32 size)
{
	_cryptoAPI.Decrypt(data, size);	
	emit DecryptSignal(data, size);
}

void CryptoApiAdapter::EncryptSlot(quint8 *data, quint32 size)
{
	_cryptoAPI.Encrypt(data, size);
	emit EncryptSignal(data, size);
}
