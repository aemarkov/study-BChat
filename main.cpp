#include "mainwindow.h"
#include <QApplication>

#include "crypto\cryptoapi.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();

	CryptoAPI api("TestCertContainer");
	api.ExportSessionKeyForUser("Garrus Vakarian");

	return 0;
}
