#include "mainwindow.h"
#include <QApplication>

#include "crypto\cryptoapi.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();

	try
	{
		uint8_t* buffer;
		uint32_t size;

		Crypto::CryptoAPI api("TestCertContainer");
		api.CreateSessionKey();
		api.ExportSessionKeyForUser("Markov Alexey", "Garrus Vakarian", &buffer, &size);

		Crypto::CryptoAPI api2("TestCertContainer");
		api2.ImportSessionKey(buffer, size, "Garrus Vakarian", "Markov Alexey");

		delete[] buffer;
	}
	catch (Crypto::CryptoException ex)
	{

	}
	catch (...)
	{

	}
	

	return 0;
}
