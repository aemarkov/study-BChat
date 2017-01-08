#include "ChatWindow.h"

/*ChatWindow::ChatWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}*/

ChatWindow::ChatWindow(Session& session):_session(session)
{
	ui.setupUi(this);

	connect(&_session, SIGNAL(UserConnected(int)), this, SLOT(UserConnected(int)));
	connect(&_session, SIGNAL(UserDisconnected(int)), this, SLOT(UserDisconnected(int)));
}

ChatWindow::~ChatWindow()
{
}


void ChatWindow::UserConnected(int)
{

}

void ChatWindow::UserDisconnected(int)
{

}
