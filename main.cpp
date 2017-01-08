#include "mainwindow.h"
#include <QApplication>
#include <fstream>

#include "util\SettingsManager\SettingsManagerContainer.h"
using namespace Util;

int main(int argc, char *argv[]) 
{		
    QApplication a(argc, argv);
	MainWindow w;
	w.show();
    return a.exec();	
}
