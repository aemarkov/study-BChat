#include "Network\Network.h"

#include "ContactsWindow\ContactsWindow.h"
#include <QApplication>
#include "crypto\cryptoapi.h"

using namespace Crypto;

int main(int argc, char *argv[])
{
	Network network;

	/*QApplication a(argc, argv);
	ContactsWindow w;
	w.show();
	return a.exec();*/

	uint8_t* keyBlob;
	uint32_t keyBlobSize;

	CryptoAPI api1("TestCertContainer");
	CryptoAPI api2("TestCertContainer");

	const char sender[] = "Responder";
	const char responder[] = "Sender";

	api1.CreateSessionKey();
	api1.ExportSessionKeyForUser(sender, responder, &keyBlob, &keyBlobSize);	
	api2.ImportSessionKey(keyBlob, keyBlobSize, responder, sender);

	uint8_t data[] = "fuck you, CryptoPRO!";
	uint32_t dataSize = sizeof(data);

	api1.Encrypt(data, dataSize);
	api2.Decrypt(data, dataSize);


	return 0;

}
