#include "ContactsWindow.h"

ContactsWindow::ContactsWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	connect(ui.btnSettings, SIGNAL(clicked()), this, SLOT(Settings_Click()));
	connect(ui.btnHostChat, SIGNAL(clicked()), this, SLOT(HostChat_Click()));
	connect(ui.btnJoinChat, SIGNAL(clicked()), this, SLOT(JoinChat_Click()));

	connect(&_sessionManager, SIGNAL(WaitingForConnection()), this, SLOT(Host_WaitingForConnection()));
	connect(&_sessionManager, SIGNAL(UserConnected()), this, SLOT(Host_UserConnected()));
}

ContactsWindow::~ContactsWindow()
{
}

void ContactsWindow::Settings_Click()
{
	auto settingsWindow = new SettingsWindow();
	settingsWindow->exec();
}

void ContactsWindow::JoinChat_Click()
{
}

void ContactsWindow::HostChat_Click()
{
	_sessionManager.CreateChat();
}

void ContactsWindow::Host_WaitingForConnection()
{
	ui.btnHostChat->setEnabled(false);
	ui.btnHostChat->setText("Waiting for connection");
}

void ContactsWindow::Host_UserConnected()
{
	ui.btnHostChat->setText("Connected");
}
