#include "mainwindow.h"
#include <QApplication>

#include <fstream>
#include "crypto\cryptoapi.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();

	try
	{
		uint8_t* keyBlob;
		uint32_t size;

		/*uint32_t dataSize = 1000;
		uint8_t* data = new uint8_t[dataSize];
		uint8_t* data2 = new uint8_t[dataSize];

		for (int i = 0; i < dataSize; i++)
			data[i] = '0' + i % 10;
		
		memcpy(data2, data, dataSize);*/

		Crypto::CryptoAPI api("TestCertContainer");
		api.CreateSessionKey();
		//api.ExportSessionKeyForUser("Markov Alexey", "Garrus Vakarian", &keyBlob, &size);

		Crypto::CryptoAPI api2("TestCertContainer");
		//api2.ImportSessionKey(keyBlob, size, "Garrus Vakarian", "Markov Alexey");

		//api.Encrypt(data, dataSize);
		//api.Decrypt(data, dataSize);

		//Check
		/*bool isOk = true;
		for (int i = 0; i < dataSize; i++)
		{
			if (data[i] != data2[i])
			{
				isOk = false;
				break;
			}
		}*/

		api.ExportMyCertificate("Garrus Vakarian", &keyBlob, &size);

		std::ofstream stream("D:\\Test.cer");
		stream.write((const char*)keyBlob, size);

		//delete[] keyBlob;
	}
	catch (Crypto::CryptoException ex)
	{

	}
	catch (...)
	{

	}
	

	return 0;
}
