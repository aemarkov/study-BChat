#include "ContactsWindow.h"

ContactsWindow::ContactsWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	connect(ui.btnSettings, SIGNAL(clicked()), this, SLOT(Settings_Click()));
	connect(ui.btnHostChat, SIGNAL(clicked()), this, SLOT(HostChat_Click()));
	connect(ui.btnJoinChat, SIGNAL(clicked()), this, SLOT(JoinChat_Click()));
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
	Session* session = new Session();

	try
	{
		session->JoinChat(0);
	}
	catch (Exception ex)
	{
		DialogHelper::ShowDialog(ex.Message);
		return;
	}

	StartSession(session);
}

void ContactsWindow::HostChat_Click()
{
	Session* session = new Session();
	
	try
	{
		session->CreateChat();
	}
	catch (Exception ex)
	{
		DialogHelper::ShowDialog(ex.Message);
		return;
	}

	StartSession(session);
}

void ContactsWindow::StartSession(Session* session)
{
	ui.btnHostChat->setEnabled(false);
	ui.btnJoinChat->setEnabled(false);
	
	ChatWindow* chat = new ChatWindow(session);
	chat->setAttribute(Qt::WA_DeleteOnClose);
	chat->show();
}
