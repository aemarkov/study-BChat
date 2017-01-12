#include "ContactsWindow.h"

ContactsWindow::ContactsWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	connect(ui.btnSettings, SIGNAL(clicked()), this, SLOT(Settings_Click()));
	connect(ui.btnHostChat, SIGNAL(clicked()), this, SLOT(HostChat_Click()));
	connect(ui.btnJoinChat, SIGNAL(clicked()), this, SLOT(JoinChat_Click()));

	connect(&_sessionManager, SIGNAL(SessionCreated()), this, SLOT(SessionCreated()));
	//connect(&_sessionManager, SIGNAL(UserConnected()), this, SLOT(Host_UserConnected()));
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
	//Тут Id юзера, выбранный из списка на форме
	_sessionManager.ConnectToUser(0);
}

void ContactsWindow::HostChat_Click()
{
	_sessionManager.CreateChat();
}

void ContactsWindow::SessionCreated()
{
	ui.btnHostChat->setEnabled(false);

	ChatWindow* chat = new ChatWindow(_sessionManager.GetSession());
	chat->show();
}