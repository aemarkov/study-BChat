#include "mainwindow.h"
#include <QApplication>
#include <fstream>

#include "NetworkAdapter\NetworkAdapter.h"
#include "Network\TcpListener.h"
#include "Network\Network.h"
#include "NetworkAdapter\NetworkProcessingThread.h"

#include "crypto\cryptoapi.h"

int main(int argc, char *argv[]) 
{	
    QApplication a(argc, argv);
	MainWindow w;
	w.show();

    return a.exec();	
}
