#include "Network\Network.h"

#include "mainwindow.h"
#include "ContactsWindow\ContactsWindow.h"
#include <QApplication>
#include "UserManager\UserManager.h"

int main(int argc, char *argv[])
{
	Network network;
	
	QApplication a(argc, argv);
	ContactsWindow w;
	w.show();
	return a.exec();

	return 0;

}
