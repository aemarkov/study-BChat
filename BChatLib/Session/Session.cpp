#include "Session.h"

Session::Session() :
	_frameConverter(QImage::Format_RGB444)
{
	connect(this, SIGNAL(__MyFameInput(QVideoFrame)), &_frameConverter, SLOT(FrameInput(QVideoFrame)));
	connect(&_frameConverter, SIGNAL(FrameOutput(QImage&)), this, SIGNAL(MyFrameOutput(QImage&)));

}


void Session::UserConnected(uint32_t userId, TcpClient client)
{
	auto user = UserManagerContainer::Inner()->GetUser(userId);
	SessionUser sessionUser(user, client);
	_users.insert(std::pair<uint32_t, SessionUser>(userId, sessionUser));

	
	emit UserConnected((int)userId);
}


void Session::MyFrameInput(const QVideoFrame & frame)
{
	emit __MyFameInput(frame);
}