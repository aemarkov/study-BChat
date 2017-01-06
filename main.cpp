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
		Crypto::CryptoAPI api("TestCertContainer");
		api.CreateSessionKey();
		api.ExportSessionKeyForUser("Markov Alexey", "Garrus Vakarian");
	}
	catch (Crypto::CryptoException ex)
	{

	}
	catch (...)
	{

	}
	

	return 0;
}
